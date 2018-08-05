/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:32:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 16:38:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "vehicle.h"
#include "graphics.h"

static int32_t		advance(void *object);
static int32_t		connect_nbr(void *object);

__attribute__((constructor))void	construct_vehiclecommands_set1(void)
{
	struct s_eventhold ev0 = {"advance", &advance, 7};
	struct s_eventhold ev2 = {"connect_nbr", &connect_nbr, 0};

	
	eventlookup[0] = ev0;
	eventlookup[2] = ev2;
}

static int32_t	advance(void *object)
{
	t_vehicle	*pl;

	pl = (t_vehicle *)((t_event *)object)->entity;
	printf("[COMMAND]\n  vehicle <%d> advanced\n", pl->c_fd);
	vehicle.place.advance(pl);
	communication.outgoing(pl->c_fd, "ok\n");
	graphic.transmit.vehicles.position(pl);
	SRV_CLNT.status[pl->c_fd] = PLAYER;
	event.iswaiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t	connect_nbr(void *object)
{
	t_vehicle	*pl;
	char		*num;

	bzero(SENDBUF, 1024);
	pl = (t_vehicle *)((t_event *)object)->entity;
	if (!(num = ft_itoa(SRV_GENV.connected_vehicles))
		|| !(SENDBUF = ft_strfreecat(SENDBUF, num))
		|| !(SENDBUF = strcat(SENDBUF, "\n"))
		|| (communication.outgoing(pl->c_fd, SENDBUF) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	SRV_CLNT.status[pl->c_fd] = PLAYER;
	return (EXIT_SUCCESS);
}
