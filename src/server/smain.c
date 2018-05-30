/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 12:20:21 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 19:13:33 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"


t_opts	arr_opts[] = {
	{"-p", 1, &get_port},
	{NULL, 0, NULL}
	/*
	{"-x", 1, &set_boardwidth},
	{"-y", 1, &set_boardheight},
	{"-n", 1, &get_nplayers},
	{"-c", 1, &get_maxclients},
	{"-t", 1, &get_timediv}
	*/
};


/*
static inline __attribute__((always_inline))void		set_sock(int32_t port,
		t_servenv *server)
{
	SRV_SOCK.proto = getprotobyname("tcp");
	SRV_SOCK.socklen = sizeof(struct sockaddr_in);
	SRV_SOCK.sockfd = socket(AF_INET, SOCK_STREAM, (SRV_SOCK.proto)->p_proto);
	(SRV_SOCK.address).sin_family = AF_INET;
	(SRV_SOCK.address).sin_port = htons(port);
	(SRV_SOCK.address).sin_addr.s_addr = INADDR_ANY;
	setsockopt(SRV_SOCK.sockfd, SOL_SOCKET, SO_REUSEADDR, &(SRV_SOCK.opt_val),
			sizeof(int32_t));
	setsockopt(SRV_SOCK.sockfd, SOL_SOCKET, SO_REUSEPORT, &(SRV_SOCK.opt_val),
			sizeof(int32_t));
}

static int32_t		ft_serverinit(int32_t port, t_servenv *server, char **envp)
{
	set_sock(port, server);
	if (bind(SRV_SOCK.sockfd, ((struct sockaddr *)&(SRV_SOCK.address)),
		sizeof(struct sockaddr_in)) < 0)
		return (EXIT_FAILURE);
	listen(SRV_SOCK.sockfd, 128);
	init_fd_select(SRV_SOCK.sockfd, server);
	server_config(server, envp);
#ifdef DEBUG
	ft_printf("server address and port : %s %d\n", inet_ntoa((SRV_SOCK.address).sin_addr), port);
#endif
	while ((select(SRV_SOCK.nfds, SRV_SOCK.input, NULL, NULL, NULL)) > 0)
	{
		if (ublock_dispatch(server) == EXIT_FAILURE)
			break ;
	}
	return (EXIT_SUCCESS);
}
*/

int32_t		main(int argc, char **argv, char **envp)
{
	int32_t	arg;

	arg = 0;
	envp = 0;
	if (argc < 2)
	{
		usage_warning(NULL);
		return (EXIT_FAILURE);
	}
	if (!(g_servenv = (t_servenv *)ft_memalloc(sizeof(t_servenv))))
		return (EXIT_FAILURE);
	if ((arg = ft_getopts(arr_opts, argv)) != EXIT_SUCCESS)
		usage_warning(argv[arg]);
	/*
	else
		if (!(server = (t_servenv *)ft_memalloc(sizeof(t_servenv)))
			|| ft_serverinit(ft_atoi(argv[1]), server, envp) == EXIT_FAILURE)
			perror(strerror(errno));
			*/
	return (EXIT_SUCCESS);
}
