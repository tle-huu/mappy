/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:16:44 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/14 17:37:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "server.h"
#include "board.h"
#include "events.h"
#include "player.h"
#include "egg.h"
#include "death.h"

t_opts	arr_opts[] = {
	{"p", 1, &srv_setport},
	{"x", 1, &srv_setboardx},
	{"y", 1, &srv_setboardy},
	{"n", 1, &srv_setteams},
	{"c", 1, &srv_setmaxclients},
	{"t", 1, &srv_settimeint},
	{NULL, 0, NULL}
};

static inline __attribute__((always_inline))int32_t	init_fd_select(void)
{
	if (!(SRV_SOCK.input = (fd_set *)ft_memalloc(sizeof(fd_set)))
		|| !(SRV_SOCK.copy = (fd_set *)ft_memalloc(sizeof(fd_set))))
	{
		perror(strerror(errno));
		return (EXIT_FAILURE);
	}
	FD_ZERO(SRV_SOCK.input);
	FD_ZERO(SRV_SOCK.copy);
	FD_SET(SRV_SOCK.sockfd, SRV_SOCK.input);
	FD_COPY(SRV_SOCK.input, SRV_SOCK.copy);
	SRV_SOCK.nfds = (SRV_SOCK.sockfd + 1);
	return (EXIT_SUCCESS);
}

static inline __attribute__((always_inline))int32_t	set_sock(void)
{
	SRV_SOCK.proto = getprotobyname("tcp");
	SRV_SOCK.socklen = sizeof(struct sockaddr_in);
	SRV_SOCK.sockfd = socket(AF_INET, SOCK_STREAM, (SRV_SOCK.proto)->p_proto);
	(SRV_SOCK.address).sin_family = AF_INET;
	(SRV_SOCK.address).sin_port = htons(SRV_SOCK.port);
	(SRV_SOCK.address).sin_addr.s_addr = INADDR_ANY;
	if ((setsockopt(SRV_SOCK.sockfd, SOL_SOCKET, SO_REUSEADDR,
			&(SRV_SOCK.opt_val), sizeof(int32_t)) < 0)
		|| (setsockopt(SRV_SOCK.sockfd, SOL_SOCKET, SO_REUSEPORT,
			&(SRV_SOCK.opt_val), sizeof(int32_t)) < 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t		ft_serverinit(void)
{
	int32_t			ret;
	t_timeval		*timeout;

	ret = 0;
	timeout = NULL;
	if ((set_sock() == EXIT_FAILURE)
		|| (bind(SRV_SOCK.sockfd, ((struct sockaddr *)&(SRV_SOCK.address)),
			sizeof(struct sockaddr_in)) < 0)
		|| (listen(SRV_SOCK.sockfd, 128) < 0)
		|| (init_fd_select() == EXIT_FAILURE)
		|| (board.new() == EXIT_FAILURE)
		|| (event.queue.new() == EXIT_FAILURE)
		|| (event.pool.new() == EXIT_FAILURE)
		|| (player.pool.new() == EXIT_FAILURE)
		|| (egg.pool.new() == EXIT_FAILURE)
		|| (death.track.new() == EXIT_FAILURE))
		return (EXIT_FAILURE);
	while ((select(SRV_SOCK.nfds, SRV_SOCK.input, NULL, NULL, timeout)) >= 0)
	{
		printf("\n\nBody of Select\n\n");
		event.queue.check();
		if ((ret = game_io()) == EXIT_FAILURE)
		{
			printf("gameio failure\n");
			return (EXIT_FAILURE);
		}
		death.track.check();
		time.settimer(&timeout);
		FD_COPY(SRV_SOCK.copy, SRV_SOCK.input);
	}
	printf("EXIT\n");
	return (EXIT_SUCCESS);
}

int32_t		main(int argc, char **argv)
{
	int32_t	arg;

	arg = 0;
	if (argc < 13)
	{
		usage_warning(NULL);
		return (EXIT_FAILURE);
	}
	if (!(g_servenv = (t_servenv *)ft_memalloc(sizeof(t_servenv))))
		return (EXIT_FAILURE);
	if ((arg = ft_getopts(arr_opts, argv)) != EXIT_SUCCESS)
		usage_warning(argv[arg]);
	ft_serverinit();
	perror(strerror(errno));
	return (EXIT_SUCCESS);
}
