/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_incoming.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:37:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 17:21:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static inline __attribute__((always_inline))void	add_fd_select(int32_t sock)
{
#ifdef DEBUG
	ft_printf("fd to add : <%d>\nnfds : <%d>\n", SRV_SOCK.sockfd, SRV_SOCK.nfds);
#endif
	FD_SET(sock, SRV_SOCK.copy);
	if (SRV_SOCK.nfds <= sock)
		SRV_SOCK.nfds = (sock + 1);
}

static inline __attribute__((always_inline))int32_t	client_message(int32_t i)
{
	char	buf[PEEK];

	SRV_CLNT = i;
	if (FD_ISSET(i, SRV_SOCK.input))
	{
		if (recv(i, &buf, PEEK, MSG_PEEK | MSG_DONTWAIT) == 0)
		{
			close(i);
			FD_CLR(i, SRV_SOCK.copy);
#ifdef DEBUG
			ft_printf("Remove client from set\n");
#endif
		}
		else if (SRV_TEMP.purgatory[i] == NOT_ACCEPTED)
		{
#ifdef DEBUG
	ft_printf("client in purgatory, is trying to join a team\n");
#endif
			if (client_init() == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
//		else
//			server_client_comm(server->clients[i], server);
	}
	return (EXIT_SUCCESS);
}

static inline __attribute__((always_inline))int32_t	add_client(int32_t *newfd)
{
	*newfd = accept(SRV_SOCK.sockfd,
				(struct sockaddr *)&(SRV_SOCK.temp), &(SRV_SOCK.socklen));
	g_servenv->curr_client = *newfd;
	client_init();
#ifdef DEBUG
			ft_printf("New client connected\n");
#endif
	add_fd_select(*newfd);
	return (EXIT_SUCCESS);
}

int32_t	process_incoming(void)
{
	int32_t	newfd;
	int32_t	i;

	i = 0;
	while ((SRV_SOCK.nfds > 0) && i <= SRV_SOCK.nfds)
	{
		if (i == SRV_SOCK.sockfd && FD_ISSET(i, SRV_SOCK.input))
		{
			if (add_client(&newfd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			if (client_message(i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	FD_COPY(SRV_SOCK.copy, SRV_SOCK.input);
#ifdef DEBUG
	ft_printf("Incoming processing done\n");
#endif
	return (EXIT_SUCCESS);
}
