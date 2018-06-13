/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:11:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 14:11:05 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/* method function prototypes */
static int32_t	outgoing(int32_t cl, char *str);
static int32_t	incoming(t_player *p);
static int32_t	printraw(int32_t cl);

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
	bzero(g_servenv.recievebuf, 513);
	if ((ret = recv(pl->c_fd, g_servenv.recievebuf, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		client.disconnect(pl->c_fd);
		return (-1);
	}
	g_servenv.recievebuf[(ret - 1)] = '\0';
	return (EXIT_SUCCESS);
}

static int32_t	incoming(int32_t cl)
{
	t_player	*pl;
	t_graphic	*gr;
	int32_t		ret;

	if (SRV_ALLP.status == GRAPHIC)
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

static int32_t	printraw(int32_t cl)
{

	printf("Unknown command, raw buffer of recieved message:\n\n|%s|\n\n",
			((SRV_ALLP.lookup)[cl])->buf);
	return (EXIT_SUCCESS);
}
