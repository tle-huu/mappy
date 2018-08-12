/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 19:48:48 by tle-huu-         ###   ########.fr       */
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
static int32_t	goal(t_vehicle *vl);
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
	if (((server.sendbuf = strcat(server.sendbuf, num)) == NULL)
		|| ((server.sendbuf = strcat(server.sendbuf, " ")) == NULL))
		return (EXIT_FAILURE);
	num = ft_itoa(vl->location.y);
	if (((server.sendbuf = strcat(server.sendbuf, num)) == NULL)
		|| ((server.sendbuf = strcat(server.sendbuf, " ")) == NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t	exited(t_vehicle *vl)
{
	char *num;

	printf("START\ttransmit.vehicles.exited()\n");
	server.sendbuf = strcat(server.sendbuf, "pdi ");
	if (_tileloc(vl) == EXIT_FAILURE)
	{
		bzero(server.sendbuf, server.nsend);
		return (EXIT_FAILURE);
	}
	num = ft_itoa((int32_t)(vl->vehicle_id));
	if (((server.sendbuf = strcat(server.sendbuf, num)) == NULL)
		|| ((server.sendbuf = strcat(server.sendbuf, "\n")) == NULL)
		|| (communication.graphical(NULL, server.sendbuf) == EXIT_FAILURE))
		;
	bzero(server.sendbuf, server.nsend);
	printf("END\ttransmit.vehicles.exited()\n");
	return (EXIT_SUCCESS);
}

static int32_t	datagram_pass(t_vehicle *vl)
{
	char	*num;

	server.sendbuf = strcat(server.sendbuf, server.recvbuf);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.vehicles(vl, server.sendbuf, 0);
	server.sendbuf[(strlen(server.sendbuf) - 1)] = ' ';
	num = ft_itoa((int32_t)vl->vehicle_id);
	server.sendbuf = strcat(server.sendbuf, num);
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
	server.sendbuf = strcat(server.sendbuf, num);
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
		server.sendbuf = strcat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, " ");
		_tileloc(vl);
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == GRAPHICAL)
			communication.graphical(NULL, server.sendbuf);
		bzero(server.sendbuf, server.nsend);
	}
	return (EXIT_SUCCESS);
}

// if new cars join, and recieve the whole map, old cars on the map will receive
// "done"
static void	_donestamp(void)
{
	if (transmit.flag != VEHICLE)
		return ;
	communication.vehicles(NULL, "done\n", 0);
	sleep(1);
	communication.vehicles(NULL, "start\n", 0);
	gettimeofday(&server.starting_time, NULL);

}

static int32_t all(void *trans)
{
	t_dblist	*temp;
	t_vehicle	*vl;
	char		*num;

	temp = vehicle.data.first;
	while (temp)
	{
		//printf("TRANSMIT THIS ALL\n");
		vl = (t_vehicle *)(temp->data);
		server.sendbuf = strcat(server.sendbuf, "pnw ");
		num = ft_itoa((int32_t)(vl->vehicle_id));
		server.sendbuf = strcat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, " ");
		_tileloc(vl);
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == VEHICLE)
			communication.vehicles(vl, server.sendbuf, 0);
		else if (transmit.flag == GRAPHIC)
			communication.graphical(trans, server.sendbuf);
		bzero(server.sendbuf, server.nsend);
		temp = temp->next;
	}
	_donestamp();
	return (EXIT_SUCCESS);
}

static int32_t	goal(t_vehicle *vl)
{
	char		*num;

	server.sendbuf = strcat(server.sendbuf, "des ");
	num = ft_itoa(vl->goal.x);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(vl->goal.y);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.vehicles(vl, server.sendbuf, 1);
	communication.graphical(NULL, server.sendbuf);
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
