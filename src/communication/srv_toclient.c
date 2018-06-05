/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_toclient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:33:47 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/04 19:05:34 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "communication.h"

/* method function prototypes */
static int32_t	message(char *str);
static int32_t	recieve(t_player *p);

t_communicate communicate = {
	/* methods */
	{
		&message
	},
	{
		&recieve
	}
};

/*
**	srv_toclient
*/

static int32_t	message(char *str)
{
	if (send(SRV_CLNT, str, strlen(str), 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	client_toserver
*/

static int32_t	recieve(t_player *p)
{
	int32_t	ret;

	printf("Recieving message from client <%d>\n", p->c_fd);
	ret = 0;
	bzero(p->buf, 513);
	if ((ret = recv(p->c_fd, p->buf, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		close(p->c_fd);
		FD_CLR(p->c_fd, SRV_SOCK.copy);
		return (-1);
	}
	p->buf[(ret - 1)] = '\0';
	return (EXIT_SUCCESS);
}
