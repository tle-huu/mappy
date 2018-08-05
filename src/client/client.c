/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:49:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "client.h"
#include "communication.h"
#include "events.h"
#include "vehicle.h"
#include "graphics.h"

static int32_t	new(void);
static void		disconnect(int32_t cl);
static void		crash(int32_t cl);

__attribute__((constructor))void	construct_client(void)
{
	client.new = &new;
	client.disconnect = &disconnect;
	client.crash = &crash;
}

static inline __attribute__((always_inline))void	add_fd_select(int32_t sock)
{
	printf("fd to add : <%d>\ncurrent nfds : <%d>\n", sock, SRV_SOCK.nfds);
	FD_SET(sock, SRV_SOCK.copy);
	if (SRV_SOCK.nfds <= sock)
		SRV_SOCK.nfds = (sock + 1);
}

static int32_t		new(void)
{
	int32_t	newfd;
	int32_t	ret;

	ret = EXIT_SUCCESS;
	newfd = accept(SRV_SOCK.sockfd,
				(struct sockaddr *)&(SRV_SOCK.temp), &(SRV_SOCK.socklen));
	(SRV_CLNT.status)[newfd] = NOT_ACCEPTED;
	add_fd_select(newfd);
	ret = communication.outgoing(newfd, "WELCOME\n");
	printf("New client %d connected\n", newfd);
	return (ret);
}

static void			crash(int32_t cl)
{
	client.disconnect(cl);
	if (SRV_CLNT.lookup[cl])
		event.removeall(SRV_CLNT.lookup[cl]);
	if ((SRV_CLNT.status[cl] != GRAPHIC)
		&& (SRV_CLNT.status[cl] != NOT_ACCEPTED))
	{
		graphic.transmit.vehicles.death(SRV_CLNT.lookup[cl]);
		vehicle.pool.add(SRV_CLNT.lookup[cl]);
	}
	if (SRV_CLNT.status[cl] == GRAPHIC)
		graphic.clear(SRV_CLNT.lookup[cl]);
}

static void			disconnect(int32_t cl)
{
	printf("Remove client <%d> from fdset and lookup\n", cl);
	close(cl);
	FD_CLR(cl, SRV_SOCK.copy);
	printf("  Client removed\n");
}