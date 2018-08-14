/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/13 17:32:31 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "vehicle.h"
#include "board.h"

static void		onboard(t_vehicle *vl);
static void		goal(t_vehicle *vl);

__attribute__((constructor))void	construct_vehicleplace(void)
{
	vehicle.place.onboard = &onboard;
	vehicle.place.goal = &goal;
}

static void		goal(t_vehicle *vl)
{
	int8_t			road;
	static int32_t	x;
	static int32_t	y;
	
	road = 0;
	if (!board.data.goal
		|| (board.data.des > 1 && !(server.simenv.connected_vehicles %
				(server.simenv.maxinitial_clients / board.data.des))))
	{
		while (!road)
		{
			x = arc4random_uniform((uint32_t)board.data.x + 1);
			y = arc4random_uniform((uint32_t)board.data.y + 1);
			road = (board.data.tiles)[x].column[y].state;
		}
		board.data.goal = 1;
	}
	vl->goal.x = x;
	vl->goal.y = y;
}

static void		onboard(t_vehicle *vl)
{
	int8_t			road;
	static int32_t	x;
	static int32_t	y;

	road = 0;
	x = 0;
	y = 0;
	if (!board.data.starts
		|| (board.data.starts && !(server.simenv.connected_vehicles %
				(server.simenv.maxinitial_clients / board.data.starts))))
	{
		while (!road
				|| (x == vl->goal.x && y == vl->goal.y))
		{
			x = arc4random_uniform((uint32_t)board.data.x + 1);
			y = arc4random_uniform((uint32_t)board.data.y + 1);
			road = (board.data.tiles)[x].column[y].state;
		}
	}
	vl->location.x = x;
	vl->location.y = y;
}
