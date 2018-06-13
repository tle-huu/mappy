/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:08:10 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 22:15:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int32_t		eat(void *entity);

__attribute__((constructor))void	construct_serverevents(void)
{
	eventlookup[2] = {NULL, &eat, 126};
	eventlookup[3] = {NULL, &egg.hatch, 600};
}

static int32_t	eat(void *entity)
{
	t_player	*pl;

	pl = (t_player *)entity;
	inventory.rm_food(pl->inventory.items);
	if (!(FOOD(pl->inventory.items)))
		player.impendingdeath(pl);
	else
		player.eating(pl);
	return (EXIT_SUCCESS);
}
