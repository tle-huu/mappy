/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 12:11:46 by nkouris          ###   ########.fr       */
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
	vehicle.place.advance = &advance;
	vehicle.place.goal = &goal;
}

static void		goal(t_vehicle *vl)
{
	int8_t		road;
	
	road = 0;
	while (!road)
	{
		vl->goal.x = arc4random_uniform((uint32_t)board.data.x);
		vl->goal.y = arc4random_uniform((uint32_t)board.data.y);
		road = (board.data.tiles)[vl->goal.x].column[vl->goal.y].state;
	}
}

static void		onboard(t_vehicle *vl)
{
	int8_t	road;

	road = 0;
	while (!road)
	{
		vl->location.x = arc4random_uniform((uint32_t)board.data.x);
		vl->location.y = arc4random_uniform((uint32_t)board.data.y);
		vl->location.orientation = 1 << (arc4random_uniform((uint32_t)3));
		road = (board.data.tiles)[vl->location.x].column[vl->location.y].state;
	}
	board.setvehicle(vl);
}

static void		advance(t_vehicle *vl)
{
	board.removevehicle(vl);
	if (vl->location.orientation & NORTH)
		(vl->location.y == 0) ? vl->location.y = board.data.y :
			(vl->location.y)--;
	else if (vl->location.orientation & SOUTH)
		(vl->location.y == board.data.y) ? vl->location.y = 0 :
			(vl->location.y)++;
	else if (vl->location.orientation & WEST)
		(vl->location.x == 0) ? vl->location.x = board.data.x :
			(vl->location.x)--;
	else if (vl->location.orientation & EAST)
		(vl->location.x == board.data.x) ? vl->location.x = 0 :
			(vl->location.x)++;
	board.setvehicle(vl);
}
