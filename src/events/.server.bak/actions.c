/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:08:10 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/21 12:18:03 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "board.h"
#include "inventory.h"
#include "graphics.h"
#include "vehicle.h"
#include "egg.h"

static int32_t		eat(void *object);
static int32_t		rec_gen(void *object);

__attribute__((constructor))void	construct_serverevents(void)
{
	struct s_eventhold	ev_eat = {"-- eat --", &eat, 126};
	struct s_eventhold	ev_egg = {"-- hatch --", egg.hatch, 600};
	struct s_eventhold	ev_resourcegen = {"-- resource --", &rec_gen, 2520};

	eventlookup[EAT] = ev_eat;
	eventlookup[EGGCOMMAND] = ev_egg;
	eventlookup[REC_GEN] = ev_resourcegen;
}

static int32_t	eat(void *object)
{
	t_vehicle	*pl;

	pl = (t_vehicle *)(((t_event *)object)->entity);
	printf("[ACTION]\n  -- Eating --\n  Player @ : <%d>\n", pl->c_fd);
	inventory.remove(&(pl->inventory.items), 0);
	printf("  Food left : <%llu>\n", FOOD(pl->inventory.items));
	if (!(FOOD(pl->inventory.items)))
		vehicle.death.soon(pl);
	else
		vehicle.eats(pl);
	return (EXIT_SUCCESS);
}

static int32_t	rec_gen(__attribute__((unused))void *object)
{
	board.resource_gen();
	graphic.transmit.tiles.all(NULL);
	return (EXIT_SUCCESS);
}
