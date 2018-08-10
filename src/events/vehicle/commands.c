/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:32:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/09 21:44:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "events.h"
#include "communication.h"
#include "vehicle.h"
#include "graphics.h"
#include "transmit.h"

static int32_t		advance(void *object);
static int32_t		connect_nbr(void *object);

__attribute__((constructor))void	construct_vehiclecommands_set1(void)
{
	struct s_eventhold ev0 = {"mvd", &advance, 1};
	struct s_eventhold ev2 = {"connect_nbr", &connect_nbr, 0};

	
	eventlookup[0] = ev0;
	eventlookup[2] = ev2;
}

static int32_t	advance(void *object)
{
	t_vehicle	*vl;

	vl = (t_vehicle *)((t_event *)object)->entity;
	communication.outgoing(vl->c_fd, "ok \n");
	server.clients.status[vl->c_fd] = PLAYER;
	event.iswaiting(vl);
	return (EXIT_SUCCESS);
}

static int32_t	connect_nbr(void *object)
{
	t_vehicle	*vl;
	char		*num;

	bzero(server.sendbuf, 1024);
	vl = (t_vehicle *)((t_event *)object)->entity;
	if (!(num = ft_itoa(server.simenv.connected_vehicles))
		|| !(server.sendbuf = strcat(server.sendbuf, num))
		|| !(server.sendbuf = strcat(server.sendbuf, "\n"))
		|| (communication.outgoing(vl->c_fd, server.sendbuf) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	server.clients.status[vl->c_fd] = PLAYER;
	return (EXIT_SUCCESS);
}
