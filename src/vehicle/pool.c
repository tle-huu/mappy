/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:27:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 12:09:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "vehicle.h"
#include "board.h"

static int32_t		new(void);
static t_dblist		*pop(void);
static void			add(t_vehicle *vl);

__attribute__((constructor))void	construct_vehiclepool(void)
{
	vehicle.pool.new = &new;
	vehicle.pool.pop = &pop;
	vehicle.pool.add = &add;
}

static int32_t		new(void)
{
	t_vehicle	*vl;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = MAX_CLIENTS;
	if (!(vehicle.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(vl = (t_vehicle *)calloc(1, sizeof(t_vehicle))))
			return (EXIT_FAILURE);
		vl->container.data = vl;
		vl->tilecontainer.data = vl;
		if (!(ft_enqueue(vehicle.pool.data, &(vl->container), 0)))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_dblist		*pop(void)
{
	return (ft_popfirst(vehicle.pool.data));
}

static void			add(t_vehicle *vl)
{
	ft_middel(&(vehicle.data), &(vl->commscontainer));
	server.clients.status[vl->c_fd] = 0;
	server.clients.lookup[vl->c_fd] = NULL;
	board.removevehicle(vl);
	bzero(vl, sizeof(t_vehicle));
	vl->container.data = vl;
	vl->tilecontainer.data = vl;
	ft_enqueue(vehicle.pool.data, &(vl->container), 0);
}
