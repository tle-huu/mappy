/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:32:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/12 11:48:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "events.h"
#include "communication.h"
#include "vehicle.h"
#include "graphics.h"
#include "transmit.h"

static int32_t		advance(void *object);

__attribute__((constructor))void	construct_vehiclecommands_set1(void)
{
	struct s_eventhold ev0 = {"mvd", &advance, 1};

	eventlookup[0] = ev0;
}

static int32_t	advance(void *object)
{
	t_vehicle	*vl;

	vl = (t_vehicle *)((t_event *)object)->entity;
	communication.outgoing(vl->c_fd, "ok \n");
	server.clients.status[vl->c_fd] = VEHICLE;
	return (EXIT_SUCCESS);
}
