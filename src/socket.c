/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:30:05 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/12 11:42:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"

static int32_t		init_select(void);
static int32_t		set(void);

void	__attribute__((constructor))construct_ft_socket(void)
{
	ft_socket.opt_val = 1;
	ft_socket.init_select = &init_select;
	ft_socket.set = &set;
}

static int32_t		init_select(void)
{
	if (!(ft_socket.input = (fd_set *)ft_memalloc(sizeof(fd_set)))
		|| !(ft_socket.copy = (fd_set *)ft_memalloc(sizeof(fd_set))))
	{
		perror(strerror(errno));
		return (EXIT_FAILURE);
	}
	FD_ZERO(ft_socket.input);
	FD_ZERO(ft_socket.copy);
	FD_SET(ft_socket.sockfd, ft_socket.input);
	FD_COPY(ft_socket.input, ft_socket.copy);
	ft_socket.nfds = (ft_socket.sockfd + 1);
	return (EXIT_SUCCESS);
}

static int32_t		set(void)
{
	ft_socket.proto = getprotobyname("tcp");
	ft_socket.socklen = sizeof(struct sockaddr_in);
	ft_socket.sockfd = socket(AF_INET, SOCK_STREAM, (ft_socket.proto)->p_proto);
	(ft_socket.address).sin_family = AF_INET;
	(ft_socket.address).sin_port = htons(ft_socket.port);
	(ft_socket.address).sin_addr.s_addr = INADDR_ANY;
	if ((setsockopt(ft_socket.sockfd, SOL_SOCKET, SO_REUSEADDR,
			&(ft_socket.opt_val), sizeof(int32_t)) < 0)
		|| (setsockopt(ft_socket.sockfd, SOL_SOCKET, SO_REUSEPORT,
			&(ft_socket.opt_val), sizeof(int32_t)) < 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
