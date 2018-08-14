/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/13 17:30:42 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "vehicle.h"
#include "events.h"
#include "board.h"
#include "graphics.h"
#include "client.h"
#include "communication.h"
#include "transmit.h"

static int32_t	new (int32_t cl);
static int32_t	command(t_vehicle *vl);

__attribute__((constructor)) void construct_vehicle(void)
{
	vehicle.new = &new;
	vehicle.command = &command;
}

static void		_checksimulate(void)
{
	if (server.simenv.connected_vehicles == server.simenv.maxinitial_clients)
	{
		server.flag = SIMULATE;
		transmit.flag = VEHICLE;
		transmit.vehicles.all();
	}
}

static int32_t		_greeting(t_vehicle *vl)
{
	transmit.flag = GRAPHIC;
	if (transmit.vehicles.connected(vl) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	transmit.flag = VEHICLE;
	if (transmit.tiles.mapsize(vl) == EXIT_FAILURE
		|| transmit.tiles.all(vl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	transmit.vehicles.position(vl);
	transmit.vehicles.goal(vl);
	transmit.vehicles.endtransmit(vl);
	return (EXIT_SUCCESS);
}

static void		_initialize(t_vehicle *vl)
{
	vl->tilecontainer.data = vl;
	vl->commscontainer.data = vl;
	vl->vehicle_id = (server.simenv.track_vehicleid)++;
	vehicle.place.goal(vl);
	vehicle.place.onboard(vl);
	server.simenv.connected_vehicles++;
	server.clients.status[vl->c_fd] = VEHICLE;
	server.clients.lookup[vl->c_fd] = vl;
}

static int32_t	new(int32_t cl)
{
	t_dblist	*temp;
	t_vehicle 	*vl;

	if (!(temp = vehicle.pool.pop()))
		return (EXIT_FAILURE);
	vl = (t_vehicle *)temp->data;
	vl->c_fd = cl;
	if (server.flag == SIMULATE)
	{
		client.disconnect(vl->c_fd);
		vehicle.pool.add(vl);
	}
	else
	{
		_initialize(vl);
		ft_enqueue(&(vehicle.data), &(vl->commscontainer), 0);
		if (_greeting(vl) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		_checksimulate();
	}
	return (EXIT_SUCCESS);
}

static int32_t		command(t_vehicle *vl)
{
	if (communication.incoming(vl->c_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (server.flag != SIMULATE)
		return (EXIT_SUCCESS);
	event.lookup(vl->c_fd);
	return (EXIT_SUCCESS);
}
