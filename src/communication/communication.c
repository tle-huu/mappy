/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:11:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 17:39:33 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "communication.h"
#include "client.h"

/* method function prototypes */
static int32_t	outgoing(int32_t cl, char *str);
static int32_t	incoming(int32_t cl);
static int32_t	printraw(void);

__attribute__((constructor))void	construct_communication(void)
{
	communication.outgoing = &outgoing;
	communication.incoming = &incoming;
	communication.printraw = &printraw;
}

static int32_t	from_graphic(__attribute__((unused))t_graphic *gr)
{
	return (EXIT_SUCCESS);
}

static int32_t	from_player(t_player *pl)
{
	int32_t		ret;

	printf("Recieving message from client <%d>\n", pl->c_fd);
	bzero(RECVBUF, 513);
	if ((ret = recv(pl->c_fd, RECVBUF, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		client.disconnect(pl->c_fd);
		return (-1);
	}
	RECVBUF[(ret)] = '\0';
	printf("  This is the buffer recieved |%s|\n", RECVBUF);
	return (EXIT_SUCCESS);
}

static int32_t	incoming(int32_t cl)
{
	t_player	*pl;
	t_graphic	*gr;
	int32_t		ret;

	if (SRV_ALLP.status[cl] == GRAPHIC)
	{
		gr = SRV_ALLP.lookup[cl];
		ret = from_graphic(gr);
	}
	else
	{
		pl = SRV_ALLP.lookup[cl];
		ret = from_player(pl);
	}
	return (ret);
}

static int32_t	outgoing(int32_t cl, char *str)
{
	if (send(cl, str, strlen(str), 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t	printraw(void)
{

	printf("Unknown command, raw buffer of recieved message:\n\n|%s|\n\n",
			RECVBUF);
	return (EXIT_SUCCESS);
}
