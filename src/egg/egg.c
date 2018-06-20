/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:25:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 17:37:17 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "egg.h"
#include "time.h"
#include "events.h"
#include "graphics.h"

static int32_t	incubate(t_player *pl);
static int32_t	hatch(void *entity);

__attribute__((constructor))void	construct_egg(void)
{
	egg.incubate = &incubate;
	egg.hatch = &hatch;
}

static int32_t	incubate(t_player *pl)
{
	t_dblist	*temp;
	t_egg		*eg;

	if (!(temp = egg.pool.pop()))
		return (-1);
	eg = (t_egg *)temp->data;
	eg->progenitor = pl->player_id;
	eg->container = temp;
	eg->teamindex = pl->teamindex;
	eg->egg_id = SRV_GENV.track_eggid++;
	egg.place.onboard(eg);
	event.add(&(eventlookup[EGGCOMMAND]), eg, 0);
	return (EXIT_SUCCESS);
}

static int32_t	hatch(void *object)
{
	t_team	*tm;
	t_egg	*eg;

	printf("[ACTION]\n  Hatching!\n");
	eg = (t_egg *)(((t_event *)object)->entity);
	tm = &(SRV_TEAM[eg->teamindex]);
	tm->nplayers++;
	SRV_GENV.maxingame_players++;
	printf("  Ready to enqueue egg on team\n");
	ft_enqueue(&(tm->eggqueue), eg->container, 0);
	egg.death.soon(eg);
	return (EXIT_SUCCESS);
}

