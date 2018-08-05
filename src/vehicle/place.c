/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 13:21:57 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "vehicle.h"
#include "board.h"

static void		onboard(t_vehicle *pl);
static void		advance(t_vehicle *pl);

__attribute__((constructor))void	construct_vehicleplace(void)
{
	vehicle.place.onboard = &onboard;
	vehicle.place.advance = &advance;
}

static void		onboard(t_vehicle *pl)
{
	pl->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl->location.orientation = 1 << (arc4random_uniform((uint32_t)3));
	board.setvehicle(pl);
}

static void		advance(t_vehicle *pl)
{
	board.removevehicle(pl);
	if (pl->location.orientation & NORTH)
		(pl->location.y == 0) ? pl->location.y = SRV_BORD.y :
			(pl->location.y)--;
	else if (pl->location.orientation & SOUTH)
		(pl->location.y == SRV_BORD.y) ? pl->location.y = 0 :
			(pl->location.y)++;
	else if (pl->location.orientation & WEST)
		(pl->location.x == 0) ? pl->location.x = SRV_BORD.x :
			(pl->location.x)--;
	else if (pl->location.orientation & EAST)
		(pl->location.x == SRV_BORD.x) ? pl->location.x = 0 :
			(pl->location.x)++;
	board.setvehicle(pl);
}