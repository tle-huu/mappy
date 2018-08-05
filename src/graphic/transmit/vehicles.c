/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:42:12 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"

static int32_t all(t_graphic *gr);
static int32_t position(t_vehicle *pl);
static int32_t connected(t_vehicle *pl);
static int32_t death(t_vehicle *pl);

__attribute__((constructor)) void construct_transmit_vehicles(void)
{
	graphic.transmit.vehicles.all = &all;
	graphic.transmit.vehicles.position = &position;
	graphic.transmit.vehicles.connected = &connected;
	graphic.transmit.vehicles.death = &death;
}

static int32_t _tileloc(t_vehicle *pl)
{
	char *num;

	num = ft_itoa(pl->location.x);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(pl->location.y);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t _orientation(t_vehicle *pl)
{
	char *num;

	num = NULL;
	if (pl->location.orientation & NORTH)
		num = ft_itoa(1);
	else if (pl->location.orientation & EAST)
		num = ft_itoa(2);
	else if (pl->location.orientation & SOUTH)
		num = ft_itoa(3);
	else if (pl->location.orientation & WEST)
		num = ft_itoa(4);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t	death(t_vehicle *pl)
{
	char *num;

	SENDBUF = strcat(SENDBUF, "pdi ");
	num = ft_itoa((int32_t)(pl->vehicle_id));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t position(t_vehicle *pl)
{
	char *num;

	SENDBUF = strcat(SENDBUF, "ppo ");
	num = ft_itoa((int32_t)pl->vehicle_id);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	_tileloc(pl);
	_orientation(pl);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t connected(t_vehicle *pl)
{
	char *num;

	if (pl)
	{
		SENDBUF = strcat(SENDBUF, "pnw ");
		num = ft_itoa((int32_t)(pl->vehicle_id));
		SENDBUF = ft_strfreecat(SENDBUF, num);
		SENDBUF = strcat(SENDBUF, " ");
		_tileloc(pl);
		_orientation(pl);
		SENDBUF = strcat(SENDBUF, "\n");
		communication.graphical(NULL, SENDBUF);
		bzero(SENDBUF, g_servenv->nsend);
	}
	return (EXIT_SUCCESS);
}

static int32_t all(t_graphic *gr)
{
	t_vehicle *pl;
	char *num;
	int32_t i;

	i = 0;
	while (i < SRV_SOCK.nfds)
	{
		if (SRV_CLNT.status[i] != GRAPHIC
			&& SRV_CLNT.lookup[i])
		{
			pl = SRV_CLNT.lookup[i];
			SENDBUF = strcat(SENDBUF, "pnw ");
			num = ft_itoa((int32_t)(pl->vehicle_id));
			SENDBUF = ft_strfreecat(SENDBUF, num);
			SENDBUF = strcat(SENDBUF, " ");
			_tileloc(pl);
			_orientation(pl);
			SENDBUF = strcat(SENDBUF, "\n");
			communication.graphical(gr, SENDBUF);
			bzero(SENDBUF, g_servenv->nsend);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
