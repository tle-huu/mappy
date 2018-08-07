/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 20:16:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "client.h"
#include "communication.h"
#include "transmit.h"
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
	printf("fd to add : <%d>\ncurrent nfds : <%d>\n", sock, ft_socket.nfds);
	FD_SET(sock, ft_socket.copy);
	if (ft_socket.nfds <= sock)
		ft_socket.nfds = (sock + 1);
}

static int32_t		new(void)
{
	int32_t	newfd;
	int32_t	ret;

	ret = EXIT_SUCCESS;
	newfd = accept(ft_socket.sockfd,
				(struct sockaddr *)&(ft_socket.temp), &(ft_socket.socklen));
	(server.clients.status)[newfd] = NOT_ACCEPTED;
	add_fd_select(newfd);
	ret = communication.outgoing(newfd, "WELCOME\n");
	printf("New client %d connected\n", newfd);
	return (ret);
}

static void			crash(int32_t cl)
{
	client.disconnect(cl);
	if (server.clients.lookup[cl])
		event.removeall(server.clients.lookup[cl]);
	if ((server.clients.status[cl] != GRAPHIC)
		&& (server.clients.status[cl] != NOT_ACCEPTED))
	{
		transmit.flag = GRAPHICAL;
		transmit.vehicles.exited(server.clients.lookup[cl]);
		vehicle.pool.add(server.clients.lookup[cl]);
	}
	if (server.clients.status[cl] == GRAPHIC)
		graphic.clear(server.clients.lookup[cl]);
}

static void			disconnect(int32_t cl)
{
	server.simenv.connected_vehicles--;
	printf("Remove client <%d> from fdset and lookup\n", cl);
	close(cl);
	FD_CLR(cl, ft_socket.copy);
	printf("  Client removed\n");
}
