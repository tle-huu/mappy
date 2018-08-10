/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/10 13:34:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "vehicle.h"
#include "board.h"

static void		onboard(t_vehicle *vl);
static void		advance(t_vehicle *vl);
static void		goal(t_vehicle *vl);

__attribute__((constructor))void	construct_vehicleplace(void)
{
	vehicle.place.onboard = &onboard;
	vehicle.place.goal = &goal;
}

static void		goal(t_vehicle *vl)
{
	int8_t		road = 0;
	static int32_t	x = 0;
	static int32_t	y = 0;
	
	if (!board.data.goal)
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
	int8_t	road;

	road = 0;
	while (!road)
	{
		vl->location.x = arc4random_uniform((uint32_t)board.data.x + 1);
		vl->location.y = arc4random_uniform((uint32_t)board.data.y + 1);
		vl->location.orientation = 1 << (arc4random_uniform((uint32_t)3));
		road = (board.data.tiles)[vl->location.x].column[vl->location.y].state;
	}
	board.setvehicle(vl);
}
