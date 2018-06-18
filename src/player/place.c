/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 22:58:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "egg.h"
#include "board.h"

static void		onboard(t_player *pl);
static void		onegg(t_player *pl);
static void		advance(t_player *pl);

__attribute__((constructor))void	construct_playerplace(void)
{
	player.place.onboard = &onboard;
	player.place.onegg = &onegg;
	player.place.advance = &advance;
}

static void		onboard(t_player *pl)
{
	pl->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl->location.orientation = 1 << (arc4random_uniform((uint32_t)3));
	board.setplayer(pl);
}

static void		onegg(t_player *pl)
{
	t_dblist	*temp;
	t_team		*tm;
	t_egg		*eg;

	tm = pl->team;
	temp = ft_popfirst(&(tm->eggqueue));
	eg = (t_egg *)temp->data;
	pl->location.x = eg->location.x;
	pl->location.y = eg->location.y;
	pl->location.orientation = eg->location.orientation;
	egg.pool.add(eg);
}

static void		advance(t_player *pl)
{
	board.removeplayer(pl);
	if (pl->location.orientation & NORTH)
	{
		if (pl->location.y == 0)
			pl->location.y = SRV_BORD.y;
		else
			(pl->location.y)--;
	}
	else if (pl->location.orientation & SOUTH)
	{
		if (pl->location.y == SRV_BORD.y)
			pl->location.y = 0;
		else
			(pl->location.y)++;
	}
	else if (pl->location.orientation & WEST)
	{
		if (pl->location.x == 0)
			pl->location.x = SRV_BORD.x;
		else
			(pl->location.x)--;
	}
	else if (pl->location.orientation & EAST)
	{
		if (pl->location.x == SRV_BORD.x)
			pl->location.x = 0;
		else
			(pl->location.x)++;
	}
	board.setplayer(pl);
}
