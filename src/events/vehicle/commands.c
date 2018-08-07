/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:32:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 22:33:50 by nkouris          ###   ########.fr       */
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
	struct s_eventhold ev0 = {"mvd", &advance, 7};
	struct s_eventhold ev2 = {"connect_nbr", &connect_nbr, 0};

	
	eventlookup[0] = ev0;
	eventlookup[2] = ev2;
}

static int32_t	advance(void *object)
{
	t_vehicle	*vl;

	vl = (t_vehicle *)((t_event *)object)->entity;
	printf("\n\nTHIS IS THE \"MESSAGE\" : %s\n\n", vl->message);
	printf("[COMMAND]\n  vehicle <%d> advanced\n", vl->c_fd);
//	vehicle.place.advance(vl);
	communication.outgoing(vl->c_fd, "ok\n");
//	transmit.flag = GRAPHICAL;
//	transmit.vehicles.position(vl);
//	transmit.flag = VEHICLE;
//	transmit.vehicles.position(vl);
	transmit.vehicles.datagram_pass(vl);
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
		|| !(server.sendbuf = ft_strfreecat(server.sendbuf, num))
		|| !(server.sendbuf = strcat(server.sendbuf, "\n"))
		|| (communication.outgoing(vl->c_fd, server.sendbuf) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	server.clients.status[vl->c_fd] = PLAYER;
	return (EXIT_SUCCESS);
}
