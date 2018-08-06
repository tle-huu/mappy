/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "vehicle.h"
#include "events.h"
#include "board.h"
#include "graphics.h"
#include "client.h"
#include "communication.h"

static int32_t	new (int32_t cl);
static int32_t	command(t_vehicle *pl);

__attribute__((constructor)) void construct_vehicle(void)
{
	vehicle.new = &new;
	vehicle.command = &command;
}

static void		_initialize(t_vehicle *pl)
{
	int32_t i;

	pl->vehicle_id = (server.simenv.track_vehicleid)++;
	pl->tilecontainer.data = pl;
	i = 0;
	vehicle.place.onboard(pl);
	server.clients.status[pl->c_fd] = PLAYER;
	server.clients.lookup[pl->c_fd] = pl;
}

static int32_t	new(int32_t cl)
{
	t_dblist	*temp;
	t_vehicle 	*pl;
	int32_t		ret;

	printf("[PLAYER]\n  Creating new vehicle @ : <%d>\n", cl);
	ret = 0;
	if (!(temp = vehicle.pool.pop()))
		return (EXIT_FAILURE);
	pl = (t_vehicle *)temp->data;
	pl->c_fd = cl;
	if ((!server.simenv.maxinitial_clients))
	{
		client.disconnect(pl->c_fd);
		vehicle.pool.add(pl);
	}
	else
	{
		_initialize(pl);
		server.simenv.connected_vehicles++;
		graphic.transmit.vehicles.connected(pl);
	}
	return (EXIT_SUCCESS);
}

static int32_t		command(t_vehicle *pl)
{
	if (communication.incoming(pl->c_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	event.lookup(pl->c_fd);
	return (EXIT_SUCCESS);
}
