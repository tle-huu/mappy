/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:11:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/21 12:18:07 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "communication.h"
#include "client.h"

/* method function prototypes */
static int32_t	outgoing(int32_t cl, char *str);
static int32_t	incoming(int32_t cl);
static int32_t	printraw(void);
static int32_t	newclient(int32_t cl);
static int32_t	graphical(t_graphic *gr, char *str);

__attribute__((constructor))void	construct_communication(void)
{
	communication.outgoing = &outgoing;
	communication.incoming = &incoming;
	communication.printraw = &printraw;
	communication.graphical = &graphical;
	communication.newclient = &newclient;
}

static int32_t	newclient(int32_t cl)
{
	if (communication.incoming(cl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strequ(RECVBUF, "GRAPHIC\n"))
		SRV_ALLP.status[cl] = JOINGRAPHIC;
	else
		SRV_ALLP.status[cl] = JOINTEAM;
	return (EXIT_SUCCESS);
}

static int32_t	incoming(int32_t cl)
{
	int32_t		ret;

	printf("Recieving message from client <%d>\n", cl);
	bzero(RECVBUF, 512);
	if ((ret = recv(cl, RECVBUF, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		client.disconnect(cl);
		return (-1);
	}
	RECVBUF[(ret)] = '\0';
	printf("  This is the buffer recieved |%s|\n", RECVBUF);
	return (EXIT_SUCCESS);
}

static int32_t	graphical(t_graphic *gr, char *str)
{
	t_dblist	*temp;

	if (!gr)
	{
		temp = g_servenv->graphical.first;
		while (temp)
		{
			gr = (t_graphic *)(temp->data);
			communication.outgoing(gr->c_fd, SENDBUF);
			temp = temp->next;
		}
	}
	else
		communication.outgoing(gr->c_fd, str);
	return (EXIT_SUCCESS);
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
