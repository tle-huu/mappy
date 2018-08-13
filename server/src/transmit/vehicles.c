/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/13 13:45:44 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"
#include "transmit.h"

static int32_t	all(void);
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

static void		_tileloc(t_vehicle *vl)
{
	char *num;

	num = ft_itoa(vl->location.x);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(vl->location.y);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
}

static int32_t	exited(t_vehicle *vl)
{
	char	*num;
	int32_t	ret;

	server.sendbuf = strcat(server.sendbuf, "pdi ");
	_tileloc(vl); 
	num = ft_itoa((int32_t)(vl->vehicle_id));
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	ret = communication.graphical();
	bzero(server.sendbuf, server.nsend);
	return (ret);
}

static int32_t	datagram_pass(t_vehicle *vl)
{
	char	*num;
	int32_t	ret;

	server.sendbuf = strcat(server.sendbuf, server.recvbuf);
	server.sendbuf = strcat(server.sendbuf, "\n");
	if (communication.vehicles(vl, server.sendbuf, 0) == EXIT_SUCCESS)
	{
		server.sendbuf[(strlen(server.sendbuf) - 1)] = ' ';
		num = ft_itoa((int32_t)vl->vehicle_id);
		server.sendbuf = strcat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, "\n");
		ret = communication.graphical();
	}
	else
		ret = EXIT_FAILURE;
	bzero(server.sendbuf, server.nsend);
	return (ret);
}

static int32_t position(t_vehicle *vl)
{
	char	*num;
	int32_t	ret;

	server.sendbuf = strcat(server.sendbuf, "ppo ");
	num = ft_itoa((int32_t)vl->vehicle_id);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	_tileloc(vl); 
	server.sendbuf = strcat(server.sendbuf, "\n");
	if (transmit.flag == GRAPHIC)
		ret = communication.graphical();
	else
		ret = communication.vehicles(vl, server.sendbuf, 1);
	bzero(server.sendbuf, server.nsend);
	return (ret);
}

static int32_t connected(t_vehicle *vl)
{
	char *num;
	int32_t	ret;

	server.sendbuf = strcat(server.sendbuf, "pnw ");
	num = ft_itoa((int32_t)(vl->vehicle_id));
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	_tileloc(vl);
	server.sendbuf = strcat(server.sendbuf, "\n");
	ret = communication.graphical();
	bzero(server.sendbuf, server.nsend);
	return (ret);
}

static int32_t	_startstamp(void)
{
	int32_t	ret;

	ret = communication.vehicles(NULL, "start\n", 0);
	gettimeofday(&server.starting_time, NULL);
	return (ret);
}

static int32_t	_donestamp(void)
{
	return (communication.vehicles(NULL, "done\n", 0));
}

static int32_t all(void)
{
	t_dblist	*temp;
	t_vehicle	*vl;
	char		*num;
	int32_t		ret;

	temp = vehicle.data.first;
	ret = EXIT_SUCCESS;
	while (temp && ret != EXIT_FAILURE)
	{
		vl = (t_vehicle *)(temp->data);
		server.sendbuf = strcat(server.sendbuf, "pnw ");
		num = ft_itoa((int32_t)(vl->vehicle_id));
		server.sendbuf = strcat(server.sendbuf, num);
		server.sendbuf = strcat(server.sendbuf, " ");
		_tileloc(vl); 
		server.sendbuf = strcat(server.sendbuf, "\n");
		if (transmit.flag == GRAPHIC)
			ret = communication.graphical();
		else
			ret = communication.vehicles(vl, server.sendbuf, 0);
		bzero(server.sendbuf, server.nsend);
		temp = temp->next;
	}
	if (transmit.flag != GRAPHIC)
	{
		sleep(5);
		ret = _donestamp();
		sleep(5);
		ret = _startstamp();
		sleep(5);
	}
	return (ret);
}

static int32_t	goal(t_vehicle *vl)
{
	char	*num;
	int32_t	ret;

	ret = EXIT_SUCCESS;
	server.sendbuf = strcat(server.sendbuf, "des ");
	num = ft_itoa(vl->goal.x);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(vl->goal.y);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	if (communication.vehicles(vl, server.sendbuf, 1) == EXIT_SUCCESS)
		ret = communication.graphical();
	bzero(server.sendbuf, server.nsend);
	return (ret);
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
