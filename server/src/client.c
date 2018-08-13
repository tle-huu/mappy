/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/12 16:18:45 by nkouris          ###   ########.fr       */
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
static void		sigpipe(int32_t);

__attribute__((constructor))void	construct_client(void)
{
	client.new = &new;
	client.disconnect = &disconnect;
	client.crash = &crash;
	client.sigpipe = &sigpipe;
}

static inline __attribute__((always_inline))void	add_fd_select(int32_t sock)
{
	FD_SET(sock, ft_socket.copy);
	if (ft_socket.nfds <= sock)
		ft_socket.nfds = (sock + 1);
}

static int32_t		new(void)
{
	int32_t	newfd;

	newfd = accept(ft_socket.sockfd,
				(struct sockaddr *)&(ft_socket.temp), &(ft_socket.socklen));
	if (setsockopt(newfd, SOL_SOCKET, SO_NOSIGPIPE,
			&(ft_socket.opt_val), sizeof(int32_t)) < 0)
	{
		printf("sockopt failed\n");
		return (EXIT_FAILURE);
	}
	(server.clients.status)[newfd] = NOT_ACCEPTED;
	add_fd_select(newfd);
	return (communication.outgoing(newfd, "WELCOME\n"));
}

static void			crash(int32_t cl)
{
	printf("START\tclient.crash()\n");
	client.disconnect(cl);
	if (server.clients.lookup[cl])
		event.removeall(server.clients.lookup[cl]);
	if ((server.clients.status[cl] != GRAPHIC)
		&& (server.clients.status[cl] != NOT_ACCEPTED))
	{
		transmit.flag = GRAPHIC;
		transmit.vehicles.exited(server.clients.lookup[cl]);
		vehicle.pool.add(server.clients.lookup[cl]);
		server.simenv.connected_vehicles--;
		if (!server.simenv.connected_vehicles)
			server.flag = GAMEOVER;
	}
	if (server.clients.status[cl] == GRAPHIC)
		graphic.clear(server.clients.lookup[cl]);
	printf("END\tclient.crash()\n");
}

static void			disconnect(int32_t cl)
{
	close(cl);
	FD_CLR(cl, ft_socket.copy);
	printf("\tClient removed\n");
}

static void			sigpipe(__attribute__((unused))int32_t t)
{
	server.flag = CLEPIPE;
	printf("There was a signal!\n");
}
