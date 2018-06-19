/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:09:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 21:02:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
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
	int32_t i;
	int32_t nresource;
	char *num;

	x = 0;
	while (x <= SRV_BORD.x)
	{
		y = 0;
		ft_memset((void *)SENDBUF, 0, 100);
		while (y <= SRV_BORD.y)
		{
			SENDBUF = strcat(SENDBUF, "bct ");
			num = ft_itoa(x);
			SENDBUF = ft_strfreecat(SENDBUF, num);
			SENDBUF = strcat(SENDBUF, " ");
			num = ft_itoa(y);
			SENDBUF = ft_strfreecat(SENDBUF, num);
			SENDBUF = strcat(SENDBUF, " ");
			i = 0;
			while (i < NRESOURCES)
			{
				nresource = board.tile.check(x, y, i);
				num = ft_itoa(nresource);
				SENDBUF = ft_strfreecat(SENDBUF, num);
				if (i != (NRESOURCES - 1))
					SENDBUF = strcat(SENDBUF, " ");
				i++;
			}
			SENDBUF = strcat(SENDBUF, "\n");
			communication.outgoing(gr->c_fd, SENDBUF);
			y++;
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

static int32_t one(t_graphic *gr, int32_t x, int32_t y)
{
	int32_t i;
	int32_t nresource;
	char *num;

	ft_memset((void *)SENDBUF, 0, 100);
	SENDBUF = strcat(SENDBUF, "bct ");
	num = ft_itoa(x);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(y);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	i = 0;
	while (i < NRESOURCES)
	{
		nresource = board.tile.check(x, y, i);
		num = ft_itoa(nresource);
		SENDBUF = ft_strfreecat(SENDBUF, num);
		if (i != (NRESOURCES - 1))
			SENDBUF = strcat(SENDBUF, " ");
		i++;
	}
	SENDBUF = strcat(SENDBUF, "\n");
	communication.outgoing(gr->c_fd, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}
