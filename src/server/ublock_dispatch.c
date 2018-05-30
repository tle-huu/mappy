/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ublock_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:52:33 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:50:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

void											init_fd_select(int32_t fd,
															t_servenv *server)
{
#ifdef DEBUG
	ft_printf("fd to init : <%d>\n", fd);
#endif
	if (!(SRV_SOCK.input = (fd_set *)ft_memalloc(sizeof(fd_set)))
		|| !(SRV_SOCK.copy = (fd_set *)ft_memalloc(sizeof(fd_set))))
	{
		perror(strerror(errno));
		exit (-1);
	}
	FD_ZERO(SRV_SOCK.input);
	FD_ZERO(SRV_SOCK.copy);
	FD_SET(fd, SRV_SOCK.input);
	FD_COPY(SRV_SOCK.input, SRV_SOCK.copy);
	SRV_SOCK.nfds = (fd + 1);
}

static inline __attribute__((always_inline))void	add_fd_select(int32_t fd,
															t_servenv *server)
{
#ifdef DEBUG
	ft_printf("fd to add : <%d>\nnfds : <%d>\n", fd, SRV_SOCK.nfds);
#endif
	FD_SET(fd, SRV_SOCK.copy);
	if (SRV_SOCK.nfds <= fd)
		SRV_SOCK.nfds = (fd + 1);
}

int32_t	ublock_dispatch(t_servenv *server)
{
	char	buf[42];
	int32_t	newfd;
	int32_t	i;

	i = 0;
	while ((SRV_SOCK.nfds > 0) && i <= SRV_SOCK.nfds)
	{
		if (i == SRV_SOCK.sockfd && FD_ISSET(i, SRV_SOCK.input))
		{
			newfd = accept(SRV_SOCK.sockfd, (struct sockaddr *)&(SRV_SOCK.temp), &(SRV_SOCK.socklen));
			client_init(newfd, server);
			ft_printf("client connected\n");
			add_fd_select(newfd, server);
		}
		else
		{
			server->curr_client = i;
			if (FD_ISSET(i, SRV_SOCK.input)
				&& server->clients[i]
				&& ((server->clients[i])->accepted > MAX_ATTEMPTS))
			{
				if (recv(i, &buf, 42, MSG_PEEK | MSG_DONTWAIT) == 0)
				{
#ifdef DEBUG
					ft_printf("actionable delete\n");
#endif
					close(i);
					FD_CLR(i, SRV_SOCK.copy);
				}
				else
				{
					server->curr_client = i;
					server_client_comm(server->clients[i], server);
				}
			}
		}
		i++;
	}
	FD_COPY(SRV_SOCK.copy, SRV_SOCK.input);
	ft_printf("\n<--- waiting on select --->\n");
	return (EXIT_SUCCESS);
}
