/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 00:56:39 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "client.h"
#include "communication.h"
#include "events.h"
#include "player.h"
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
	printf("<--- NEW CLIENT --->\n");
	newfd = accept(SRV_SOCK.sockfd,
				(struct sockaddr *)&(SRV_SOCK.temp), &(SRV_SOCK.socklen));
	(SRV_ALLP.status)[newfd] = NOT_ACCEPTED;
	add_fd_select(newfd);
	if (!SRV_GENV.maxinitial_clients && !SRV_GENV.maxingame_players)
	{
		client.disconnect(newfd);
		printf("Client %d rejected, not allowed\n", newfd);
	}
	else
	{
		ret = communication.outgoing(newfd, "WELCOME\n");
		printf("New client %d connected\n", newfd);
	}
	return (ret);
}

static void			crash(int32_t cl)
{
	client.disconnect(cl);
	if (SRV_ALLP.lookup[cl])
		event.removeall(SRV_ALLP.lookup[cl]);
	if ((SRV_ALLP.status[cl] != GRAPHIC)
		&& (SRV_ALLP.status[cl] != NOT_ACCEPTED))
	{
		graphic.transmit.players.death(SRV_ALLP.lookup[cl]);
		player.pool.add(SRV_ALLP.lookup[cl]);
	}
	if (SRV_ALLP.status[cl] == GRAPHIC)
		graphic.clear(SRV_ALLP.lookup[cl]);
}

static void			disconnect(int32_t cl)
{
	printf("Remove client <%d> from fdset and lookup\n", cl);
	close(cl);
	FD_CLR(cl, SRV_SOCK.copy);
	printf("  Client removed\n");
}
