/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 09:41:17 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 22:35:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"
#include "communication.h"

/* method function prototypes */
static int32_t	outgoing(int32_t cl, char *str);
static int32_t	incoming(t_player *p);
static int32_t	printraw(int32_t cl);

t_communicate communicate = {
	/* methods */
	{
		&outgoing
	},
	{
		&incoming,
		&printraw
	}
};

/*
**	srv_toclient
*/

static int32_t	outgoing(int32_t cl, char *str)
{
	if (send(cl, str, strlen(str), 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	client_toserver
*/

static int32_t	incoming(t_player *pl)
{
	int32_t	ret;

	printf("Recieving message from client <%d>\n", pl->c_fd);
	ret = 0;
	bzero(pl->buf, 513);
	if ((ret = recv(pl->c_fd, pl->buf, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		client.del(pl->c_fd);
		return (-1);
	}
	pl->buf[(ret - 1)] = '\0';
	return (EXIT_SUCCESS);
}

static int32_t	printraw(int32_t cl)
{

	printf("Unknown command, raw buffer of recieved message:\n\n|%s|\n\n",
			((SRV_ALLP.lookup)[cl])->buf);
	return (EXIT_SUCCESS);
}
