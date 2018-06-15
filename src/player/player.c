/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/15 14:59:55 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "inventory.h"
#include "events.h"

static int32_t	new(int32_t cl);
static void		eats(t_player *pl);
static void		clear(t_player *pl);

__attribute__((constructor))void	construct_player(void)
{
	player.new = &new;
	player.eats = &eats;
	player.clear = &clear;
}

static int32_t	new(int32_t cl)
{
	t_dblist	*temp;
	t_player	*pl;
	int32_t		ret;
	int32_t		i;
	
	printf("[PLAYER]\n  Creating new player @ : <%d>\n", cl);
	ret  = 0;
	i = 0;
	if (!(temp = player.pool.pop()))
		return (EXIT_FAILURE);
	pl = (t_player *)temp->data;
	pl->container = temp;
	pl->c_fd = cl;
	pl->player_id = (SRV_GENV.track_playerid)++;
	(SRV_ALLP.lookup)[cl] = pl;
	while (i++ < 10)
		pl->inventory.items = inventory.ad_food(pl->inventory.items);
	printf("  Player is on : <%p>\n", pl);
	if (player.parse.teamname(pl) == EXIT_SUCCESS)
		player.eats(pl);
	return (EXIT_SUCCESS);
}

static void		clear(t_player *pl)
{
	t_dblist	*temp;

	temp = pl->container;
	bzero(pl, sizeof(t_player));
	pl->container = temp;
}

static void		eats(t_player *pl)
{
	printf("[PLAYER]\n  Player on : <%p> eats\n", pl);
	event.add(&(eventlookup[EAT]), (void *)pl, 0);
}
