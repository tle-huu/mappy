/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:09:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:21 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"

static int32_t all(t_graphic *gr);
static int32_t one(t_graphic *gr, int32_t x, int32_t y);

__attribute__((constructor)) void construct_transmit_tiles(void)
{
	graphic.transmit.tiles.all = &all;
	graphic.transmit.tiles.one = &one;
}

static int32_t all(t_graphic *gr)
{
	int32_t x;
	int32_t y;
	char *num;

	x = 0;
	while (x <= board.data.x)
	{
		y = 0;
		while (y <= board.data.y)
		{
			server.sendbuf = strcat(server.sendbuf, "bct ");
			num = ft_itoa(x);
			server.sendbuf = ft_strfreecat(server.sendbuf, num);
			server.sendbuf = strcat(server.sendbuf, " ");
			num = ft_itoa(y);
			server.sendbuf = ft_strfreecat(server.sendbuf, num);
			server.sendbuf = strcat(server.sendbuf, "\n");
			communication.graphical(gr, server.sendbuf);
			bzero(server.sendbuf, server.nsend);
			y++;
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

static int32_t one(t_graphic *gr, int32_t x, int32_t y)
{
	char *num;

	server.sendbuf = strcat(server.sendbuf, "bct ");
	num = ft_itoa(x);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(y);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.graphical(gr, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}
