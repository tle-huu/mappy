/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:14:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 14:10:28 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static inline __attribute__((always_inline))int32_t	known_socket(int32_t cl)
{
	//add handling for graphical client
	char	buf[PEEK];

	SRV_CLNT = cl;
	if (recv(cl, &buf, PEEK, MSG_PEEK | MSG_DONTWAIT) == 0)
		client.disconnect(cl);
	else if ((SRV_ALLP.status)[cl] == NOT_ACCEPTED)
	{
		printf("client <%d> is in status, and trying to join a team\n", cl);
		player.new(cl);
	}
	else if (SRV_ALLP.status[cl] == GRAPHICAL)
		;
	else if (player.parse.command(SRV_ALLP.lookup[cl]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int32_t	game_io(void)
{
	int32_t	i;

	i = 0;
	while ((SRV_SOCK.nfds > 0) && i <= SRV_SOCK.nfds)
	{
		if (i == SRV_SOCK.sockfd && FD_ISSET(i, SRV_SOCK.input))
		{
			if (client.new() == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (FD_ISSET(i, SRV_SOCK.input))
		{
			if (known_socket(i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	FD_COPY(SRV_SOCK.copy, SRV_SOCK.input);
	printf("Incoming processing done\n");
	return (EXIT_SUCCESS);
}
