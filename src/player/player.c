/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/18 00:47:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "inventory.h"
#include "events.h"
#include "board.h"

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
	pl->tilecontainer.data = pl;
	pl->level = 1;
	(SRV_ALLP.lookup)[cl] = (void *)pl;
	while (i++ < 10)
		inventory.add(&(pl->inventory.items), 0);
	printf("  Player is on : <%p>\n", pl);
	if (player.parse.teamname(pl) == EXIT_SUCCESS)
		player.eats(pl);
	return (EXIT_SUCCESS);
}

static void		clear(t_player *pl)
{
	t_dblist	*temp;

	(SRV_ALLP.status)[pl->c_fd] = 0;
	(pl->team) ? (pl->team->players[pl->c_fd] = NULL) : 0;
	board.removeplayer(pl);
	temp = pl->container;
	bzero(pl, sizeof(t_player));
	pl->container = temp;
}

static void		eats(t_player *pl)
{
	printf("[PLAYER]\n  Player on : <%p> eats\n", pl);
	event.add(&(eventlookup[EAT]), (void *)pl, 0);
}
