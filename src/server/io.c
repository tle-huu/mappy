/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:14:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 16:15:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "server.h"
#include "client.h"
#include "player.h"
#include "graphics.h"
#include "communication.h"

static inline __attribute__((always_inline))int32_t	known_socket(int32_t cl)
{
	char	buf[PEEK];

	if (recv(cl, &buf, PEEK, MSG_PEEK | MSG_DONTWAIT) == 0)
	{
		client.crash(cl);
		return (EXIT_SUCCESS);
	}
	if (SRV_ALLP.status[cl] == NOT_ACCEPTED)
		communication.newclient(cl);
	if (SRV_ALLP.status[cl] == JOINVEHICLE)
		player.new(cl);
	else if (SRV_ALLP.status[cl] == JOINGRAPHIC)
		graphic.new(cl);
// if graphical client ever needs to speak to the server
//	else if (SRV_ALLP.status[cl] == GRAPHIC)
//		graphic.parse.request((t_graphic *)SRV_ALLP.lookup[cl])
	else if (player.command((t_player *)SRV_ALLP.lookup[cl]) == EXIT_FAILURE)
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
	printf("Incoming processing done\n");
	return (EXIT_SUCCESS);
}
