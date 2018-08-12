/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 22:11:46 by psprawka         ###   ########.fr       */
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
	if (((server.sendbuf = strcat(server.sendbuf, num)) == NULL)				//why do we even catch an exeption if we dont handle it at all?
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
	if (communication.vehicles(vl, server.sendbuf, 0) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c :82\n");
	server.sendbuf[(strlen(server.sendbuf) - 1)] = ' ';
	num = ft_itoa((int32_t)vl->vehicle_id);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	if (communication.graphical(NULL, server.sendbuf) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c :88\n");
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
	if (_tileloc(vl) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 102\n");
	server.sendbuf = strcat(server.sendbuf, "\n");
	// if (transmit.flag == VEHICLE)
	// 	communication.vehicles(vl, server.sendbuf, 1);
	if (transmit.flag == VEHICLE &&
		communication.vehicles(vl, server.sendbuf, 1) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c :108\n");
	else if (transmit.flag == GRAPHIC &&
		communication.graphical(NULL, server.sendbuf) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c :111\n");
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
		if (_tileloc(vl) == EXIT_FAILURE)
			printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 127\n");
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == GRAPHIC)											//are you sure you meant GRAPHICAL not GRAPHIC? (GRAPHIC is everywhere else)
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
	if (communication.vehicles(NULL, "done\n", 0) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 143\n");
	sleep(1);
	if (communication.vehicles(NULL, "start\n", 0) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 146\n");
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
		if (_tileloc(vl) == EXIT_FAILURE)
			printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 167\n");
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == VEHICLE && communication.vehicles(vl, server.sendbuf, 0))
			printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 170\n");
		else if (transmit.flag == GRAPHIC && communication.graphical(trans, server.sendbuf))
			printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 172\n");
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
	if (communication.vehicles(vl, server.sendbuf, 1) == EXIT_FAILURE ||
		communication.graphical(NULL, server.sendbuf) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c line 192\n");;
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t	endtransmit(void *trans)
{
	char	*done = "done\n";

	server.sendbuf = strcat(server.sendbuf, done);
	if (communication.vehicles(trans, server.sendbuf, 1) == EXIT_FAILURE)
		printf("Uncaught EXIT_FAILURE: transmit/vehicles.c :204\n");;
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}
