/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:15:52 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:51:28 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int32_t			client_init(int32_t newfd, t_servenv *server)
{
	char		*c_addr;
	t_client	*client;

	c_addr = inet_ntoa((SRV_SOCK.temp).sin_addr);
#ifdef DEBUG
	ft_printf("<--- CLIENT INIT --->\nip of client : %s\n", c_addr);
#endif
	if (!(server->clients))
	{
		if (!(server->clients = ft_memalloc(sizeof(t_client *) * FD_SETSIZE)))
			return (EXIT_FAILURE);
	}
	if (!(client = (t_client *)ft_memalloc(sizeof(t_client))))
		return (EXIT_FAILURE);
	server->curr_client = newfd;
	CLIENT_SOCK.sockfd = newfd;
	server->clients[newfd] = client;
//	server_client_comm(client, server);
#ifdef DEBUG
	ft_printf("<--- END CLIENT INIT --->\n");
#endif
	return (EXIT_SUCCESS);
}
