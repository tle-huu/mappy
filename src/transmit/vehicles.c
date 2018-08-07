/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 22:33:34 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"
#include "transmit.h"

static int32_t	all(void *trans);
static int32_t 	position(t_vehicle *vl);
static int32_t 	connected(t_vehicle *vl);
static int32_t 	exited(t_vehicle *vl);
static int32_t	goal(void *);
static int32_t	endtransmit(void *);
static int32_t	datagram_pass(t_vehicle *);

__attribute__((constructor)) void construct_transmit_vehicles(void)
{
	transmit.vehicles.all = &all;
	transmit.vehicles.position = &position;
	transmit.vehicles.connected = &connected;
	transmit.vehicles.exited = &exited;
	transmit.vehicles.goal = &goal;
	transmit.vehicles.endtransmit = &endtransmit;
	transmit.vehicles.datagram_pass = &datagram_pass;
}

static int32_t _tileloc(t_vehicle *vl)
{
	char *num;

	num = ft_itoa(vl->location.x);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(vl->location.y);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	return (EXIT_SUCCESS);
}

static int32_t	exited(t_vehicle *vl)
{
	char *num;

	server.sendbuf = strcat(server.sendbuf, "pdi ");
	_tileloc(vl);
	num = ft_itoa((int32_t)(vl->vehicle_id));
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.graphical(NULL, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t	datagram_pass(t_vehicle *vl)
{
	server.sendbuf = strcat(server.sendbuf, "mvd ");
	server.sendbuf = strcat(server.sendbuf, vl->message);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.graphical(NULL, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t position(t_vehicle *vl)
{
	char *num;

	server.sendbuf = strcat(server.sendbuf, "ppo ");
	num = ft_itoa((int32_t)vl->vehicle_id);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	_tileloc(vl);
	server.sendbuf = strcat(server.sendbuf, "\n");
	if (transmit.flag == VEHICLE)
		communication.vehicles(vl, server.sendbuf, 1);
	else if (transmit.flag == GRAPHIC)
		communication.graphical(NULL, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t connected(t_vehicle *vl)
{
	char *num;

	if (vl)
	{
		server.sendbuf = strcat(server.sendbuf, "pnw ");
		num = ft_itoa((int32_t)(vl->vehicle_id));
		server.sendbuf = ft_strfreecat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, " ");
		_tileloc(vl);
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == GRAPHICAL)
			communication.graphical(NULL, server.sendbuf);
		bzero(server.sendbuf, server.nsend);
	}
	return (EXIT_SUCCESS);
}

static int32_t all(void *trans)
{
	t_dblist	*temp;
	t_vehicle	*vl;
	char		*num;

	temp = vehicle.data.first;
	while (temp)
	{
		printf("TRANSMIT THIS ALL\n");
		vl = (t_vehicle *)(temp->data);
		server.sendbuf = strcat(server.sendbuf, "pnw ");
		num = ft_itoa((int32_t)(vl->vehicle_id));
		server.sendbuf = ft_strfreecat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, " ");
		_tileloc(vl);
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == VEHICLE)
		{
			communication.vehicles(vl, server.sendbuf, 0);
		}
		else if (transmit.flag == GRAPHIC)
			communication.graphical(trans, server.sendbuf);
		bzero(server.sendbuf, server.nsend);
		temp = temp->next;
	}
	communication.vehicles(NULL, "done\n", 0);
	sleep(1);
	communication.vehicles(NULL, "start\n", 0);
	return (EXIT_SUCCESS);
}

static int32_t	goal(void *trans)
{
	int32_t		x;
	int32_t		y;
	char		*num;

	x = arc4random_uniform((uint32_t)board.data.x);
	y = arc4random_uniform((uint32_t)board.data.y);
	server.sendbuf = strcat(server.sendbuf, "des ");
	num = ft_itoa(x);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(y);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.vehicles(trans, server.sendbuf, 1);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t	endtransmit(void *trans)
{
	char	*done = "done\n";

	server.sendbuf = strcat(server.sendbuf, done);
	communication.vehicles(trans, server.sendbuf, 1);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}
