/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:27:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "vehicle.h"
#include "board.h"

static int32_t		new(void);
static t_dblist		*pop(void);
static void			add(t_vehicle *pl);

__attribute__((constructor))void	construct_vehiclepool(void)
{
	vehicle.pool.new = &new;
	vehicle.pool.pop = &pop;
	vehicle.pool.add = &add;
}

static int32_t		new(void)
{
	t_vehicle	*pl;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = MAX_CLIENTS;
	if (!(vehicle.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(pl = (t_vehicle *)calloc(1, sizeof(t_vehicle))))
			return (EXIT_FAILURE);
		pl->container.data = pl;
		pl->tilecontainer.data = pl;
		if (!(ft_enqueue(vehicle.pool.data, &(pl->container), 0)))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_dblist		*pop(void)
{
	return (ft_popfirst(vehicle.pool.data));
}

static void			add(t_vehicle *pl)
{
	server.clients.status[pl->c_fd] = 0;
	server.clients.lookup[pl->c_fd] = NULL;
	board.removevehicle(pl);
	bzero(pl, sizeof(t_vehicle));
	pl->container.data = pl;
	pl->tilecontainer.data = pl;
	ft_enqueue(vehicle.pool.data, &(pl->container), 0);
}
