/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:16:44 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 00:48:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "server.h"
#include "board.h"
#include "events.h"
#include "vehicle.h"

void	__attribute((constructor))construct_getopts(void)
{
	construct_servergetopts();
	struct s_opts	opt0 = {"p", 1, server.opts.port};
	struct s_opts	opt1 = {"x", 1, server.opts.boardx};
	struct s_opts	opt2 = {"y", 1, server.opts.boardy};
	struct s_opts	opt3 = {"c", 1, server.opts.maxclients};
	struct s_opts	opt4 = {"t", 1, server.opts.timeinterval};
	struct s_opts	opt5 = {NULL, 0, NULL};

	arr_opts[0] = opt0;
	arr_opts[1] = opt1;
	arr_opts[2] = opt2;
	arr_opts[3] = opt3;
	arr_opts[4] = opt4;
	arr_opts[5] = opt5;

//	t_opts arr_opts[6] = {
//		{"p", 1, server.opts.port},
//		{"x", 1, server.opts.boardx},
//		{"y", 1, server.opts.boardy},
//		{"c", 1, server.opts.maxclients},
//		{"t", 1, server.opts.timeinterval},
//		{NULL, 0, NULL}
//	};
}

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

static int32_t		ft_initializers(void)
{
	if ((set_sock() == EXIT_FAILURE)
		|| (bind(SRV_SOCK.sockfd, ((struct sockaddr *)&(SRV_SOCK.address)),
			sizeof(struct sockaddr_in)) < 0)
		|| (listen(SRV_SOCK.sockfd, 128) < 0)
		|| (init_fd_select() == EXIT_FAILURE)
		|| (event.queue.new() == EXIT_FAILURE)
		|| (event.pool.new() == EXIT_FAILURE)
		|| (vehicle.pool.new() == EXIT_FAILURE)
		|| (board.new() == EXIT_FAILURE)
		|| !(SENDBUF = calloc(1, 1024)))
		return (EXIT_FAILURE);
	g_servenv->nsend = 1024;
	return (EXIT_SUCCESS);
}

static int32_t		ft_serverinit(void)
{
	int32_t			ret;
	t_timeval		*timeout;

	ret = 0;
	timeout = NULL;
	if (ft_initializers() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while ((select(SRV_SOCK.nfds, SRV_SOCK.input, NULL, NULL, timeout)) >= 0)
	{
		printf("\n[SELECT]\n  Body of Select\n");
		event.queue.check();
		if ((ret = server.io()) == EXIT_FAILURE)
			ft_printf("gameio failure\n");
		time.settimer(&timeout);
		FD_COPY(SRV_SOCK.copy, SRV_SOCK.input);
		printf("\n[SELECT]\n  End of cycle\n");
	}
	printf("EXIT\n");
	return (EXIT_SUCCESS);
}

int32_t		main(int argc, char **argv)
{
	int32_t	arg;

	arg = 0;
	if (argc < 11)
	{
		server.usagewarning(NULL);
		return (EXIT_FAILURE);
	}
	if (!(g_servenv = (t_servenv *)ft_memalloc(sizeof(t_servenv))))
		return (EXIT_FAILURE);
	if ((arg = ft_getopts(arr_opts, argv)) != EXIT_SUCCESS)
		server.usagewarning(argv[arg]);
	ft_serverinit();
	perror(strerror(errno));
	return (EXIT_SUCCESS);
}
