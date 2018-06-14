/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:08:10 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 22:14:09 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "inventory.h"
#include "player.h"
#include "egg.h"

static int32_t		eat(void *entity);

__attribute__((constructor))void	construct_serverevents(void)
{
	struct s_eventhold	ev2 = {NULL, &eat, 126};
	struct s_eventhold	ev3 = {NULL, egg.hatch, 600};

	eventlookup[2] = ev2;
	eventlookup[3] = ev3;
}

static int32_t	eat(void *entity)
{
	t_player	*pl;

	pl = (t_player *)entity;
	inventory.rm_food(pl->inventory.items);
	if (!(FOOD(pl->inventory.items)))
		player.death.soon(pl);
	else
		player.eats(pl);
	return (EXIT_SUCCESS);
}
