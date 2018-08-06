/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
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
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(pl->location.y);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
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
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	return (EXIT_SUCCESS);
}

static int32_t	death(t_vehicle *pl)
{
	char *num;

	server.sendbuf = strcat(server.sendbuf, "pdi ");
	num = ft_itoa((int32_t)(pl->vehicle_id));
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.graphical(NULL, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t position(t_vehicle *pl)
{
	char *num;

	server.sendbuf = strcat(server.sendbuf, "ppo ");
	num = ft_itoa((int32_t)pl->vehicle_id);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	_tileloc(pl);
	_orientation(pl);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.graphical(NULL, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t connected(t_vehicle *pl)
{
	char *num;

	if (pl)
	{
		server.sendbuf = strcat(server.sendbuf, "pnw ");
		num = ft_itoa((int32_t)(pl->vehicle_id));
		server.sendbuf = ft_strfreecat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, " ");
		_tileloc(pl);
		_orientation(pl);
		server.sendbuf = strcat(server.sendbuf, "\n");
		communication.graphical(NULL, server.sendbuf);
		bzero(server.sendbuf, server.nsend);
	}
	return (EXIT_SUCCESS);
}

static int32_t all(t_graphic *gr)
{
	t_vehicle *pl;
	char *num;
	int32_t i;

	i = 0;
	while (i < ft_socket.nfds)
	{
		if (server.clients.status[i] != GRAPHIC
			&& server.clients.lookup[i])
		{
			pl = server.clients.lookup[i];
			server.sendbuf = strcat(server.sendbuf, "pnw ");
			num = ft_itoa((int32_t)(pl->vehicle_id));
			server.sendbuf = ft_strfreecat(server.sendbuf, num);
			server.sendbuf = strcat(server.sendbuf, " ");
			_tileloc(pl);
			_orientation(pl);
			server.sendbuf = strcat(server.sendbuf, "\n");
			communication.graphical(gr, server.sendbuf);
			bzero(server.sendbuf, server.nsend);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
