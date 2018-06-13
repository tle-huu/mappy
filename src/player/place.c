/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 13:20:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		onboard(t_player *pl);
static void		onegg(t_player *pl);

__attribute__((constructor))void	construct_playerpool(void)
{
	player.place.onboard = &onboard;
	player.place.onegg = &onegg;
}

static void		onboard(t_player *pl)
{
	t_player	*pl;

	pl = (SRV_ALLP.lookup)[cl];
	pl->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl->location.orientation = arc4random_uniform((uint32_t)4);
	board.setplayer(cl);
}

static void		onegg(t_player *pl)
{
	t_dblist	*temp;
	t_team		*tm;
	t_egg		*egg;

	tm = pl->team;
	temp = ft_popfirst(tm->eggqueue);
	egg = (t_egg *)temp->data;
	pl->location.x = egg->location.x;
	pl->location.y = egg->location.y;
	pl->location.orientation = egg->location.orientation;
	egg.death.pop(egg);
	egg.pool.add(egg);
}
