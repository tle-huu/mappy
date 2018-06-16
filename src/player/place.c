/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/15 17:48:43 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "egg.h"
#include "board.h"

static void		onboard(t_player *pl);
static void		onegg(t_player *pl);

__attribute__((constructor))void	construct_playerplace(void)
{
	player.place.onboard = &onboard;
	player.place.onegg = &onegg;
}

static void		onboard(t_player *pl)
{
	pl->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl->location.orientation = arc4random_uniform((uint32_t)4);
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
