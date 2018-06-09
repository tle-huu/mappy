/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:14:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 16:44:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"
#include "communication.h"
#include "player.h"
#include "team.h"

static inline __attribute__((always_inline))int32_t	known_socket(int32_t cl)
{
	char	buf[PEEK];

	SRV_CLNT = cl;
	if (recv(cl, &buf, PEEK, MSG_PEEK | MSG_DONTWAIT) == 0)
		client.del(cl);
	else if ((SRV_ALLP.client_stat)[cl] == NOT_ACCEPTED)
	{
		printf("client <%d> is in client_stat, and trying to join a team\n", cl);
		if (SRV_ALLP.lookup[cl])
		{
			player.add_toteam(cl);
			player.placeonboard(cl);
		}
		else
			client.isplayer(cl);
	}
	else if (player.parse_command(cl) == EXIT_FAILURE)
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
