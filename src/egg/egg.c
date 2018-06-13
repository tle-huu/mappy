/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:25:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 23:59:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egg.h"

static int32_t	incubate(t_player *pl);
static int32_t	hatch(void *entity);

__attribute__((constructor))void	construct_egg(void)
{
	egg.incubate = &new;
	egg.hatch = &add;
}

static int32_t	incubate(t_player *pl)
{
	t_dblist	*temp;
	t_egg		*eg;

	if (!(temp = egg.popfrompool()))
		return (-1);
	egg = (t_egg *)temp->data;
	egg->container = temp;
	egg->teamindex = pl->teamindex;
	egg->egg_id = SRV_GENV.track_eggid++;
	egg.placeonboard(egg);
	command.add(&(commandlookup[EGGCOMMAND]), egg->container);
}

static int32_t	hatch(t_egg *eg)
{
	t_team		*team;

	// add to the queue of eggs available on a team (basically only there
	// for reference as a tile the newly connected client will go to
	team = SRV_TEAM[eg->teamindex];
	team->nplayers++;
	SRV_GENV.maxingame_players++;
	ft_enqueue(team->eggs, eg->deathcontainer, 0);
	egg.death.soon(egg);
}

