/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:43:47 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 16:03:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "events.h"
#include "client.h"
#include "vehicle.h"
#include "graphics.h"
#include "communication.h"

static void			warning(char *str);
static int32_t		io(void);
static int32_t		new(void);

void		__attribute((constructor))construct_server(void)
{
	server.io = &io;
	server.usagewarning = &warning;
	server.new = &new;
}

static int32_t		initializers(void)
{
	if ((ft_socket.set() == EXIT_FAILURE)
		|| (bind(ft_socket.sockfd, ((struct sockaddr *)&(ft_socket.address)),
			sizeof(struct sockaddr_in)) < 0)
		|| (listen(ft_socket.sockfd, 128) < 0)
		|| (ft_socket.init_select() == EXIT_FAILURE)
		|| (event.queue.new() == EXIT_FAILURE)
		|| (event.pool.new() == EXIT_FAILURE)
		|| (vehicle.pool.new() == EXIT_FAILURE)
		|| (server.opts.boardType == XYMAP && board.new() == EXIT_FAILURE)
		|| (server.opts.boardType == LOADMAP && board.load_file() == EXIT_FAILURE)
		|| !(server.sendbuf = calloc(1, 1024)))
		return (EXIT_FAILURE);
	server.nsend = 1024;
	return (EXIT_SUCCESS);
}

static int32_t		new(void)
{
	int32_t			ret;
	t_timeval		*timeout;

	ret = 0;
	timeout = NULL;
	if (initializers() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while ((select(ft_socket.nfds, ft_socket.input, NULL, NULL, timeout)) >= 0)
	{
	//	printf("\n[SELECT]\n  Body of Select\n");
		event.queue.check();
		if ((ret = server.io()) == EXIT_FAILURE)
			printf("gameio failure\n");
		time.settimer(&timeout);
		FD_COPY(ft_socket.copy, ft_socket.input);
	//	printf("\n[SELECT]\n  End of cycle\n");
	}
	//printf("EXIT\n");
	return (EXIT_SUCCESS);
}

static inline int32_t	__attribute__((always_inline))known_socket(int32_t cl)
{
	char	buf[PEEK];

	if (recv(cl, &buf, PEEK, MSG_PEEK | MSG_DONTWAIT) == 0)
	{
		client.crash(cl);
		return (EXIT_SUCCESS);
	}
	if (server.clients.status[cl] == NOT_ACCEPTED)
	{
		if (communication.newclient(cl) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (server.clients.status[cl] == JOINVEHICLE)
		vehicle.new(cl);
	else if (server.clients.status[cl] == JOINGRAPHIC)
		graphic.new(cl);
// if graphical client ever needs to speak to the server
//	else if (server.clients.status[cl] == GRAPHIC)
//		graphic.parse.request((t_graphic *)server.clients.lookup[cl])
	else if (vehicle.command((t_vehicle *)server.clients.lookup[cl]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t		io(void)
{
	int32_t	i;

	i = 0;
	while ((ft_socket.nfds > 0) && i <= ft_socket.nfds)
	{
		if (i == ft_socket.sockfd && FD_ISSET(i, ft_socket.input))
		{
			if (client.new() == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (FD_ISSET(i, ft_socket.input))
		{
			if (known_socket(i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	//printf("Incoming processing done\n");
	return (EXIT_SUCCESS);
}

static void		warning(char *str)
{
	if (str)
		printf("Illegal option: %s\n\n", str);
	printf("USAGE:\n\
./server -p <port> [-x <width> -y <height>] || [-f <filename>]\
-c <nb> -t <t>\n\n-p port number\n-x world width\n-y world height\n\
-c number of vehicles allowed in simulation\n-t time unit\
(the greater t is, the faster the simulation will run)\n\n");
}
