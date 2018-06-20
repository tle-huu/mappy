/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 01:17:21 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "inventory.h"
#include "events.h"
#include "board.h"
#include "team.h"
#include "graphics.h"
#include "client.h"
#include "communication.h"

static int32_t	new (int32_t cl);
static void		eats(t_player *pl);
static int32_t	command(t_player *pl);

__attribute__((constructor)) void construct_player(void)
{
	player.new = &new;
	player.eats = &eats;
	player.command = &command;
}

static void		_initialize(t_player *pl)
{
	int32_t i;

	pl->player_id = (SRV_GENV.track_playerid)++;
	pl->tilecontainer.data = pl;
	pl->level = 1;
	i = 0;
	while (i++ < 10)
		inventory.add(&(pl->inventory.items), 0);
	if (pl->team->eggqueue.first)
		player.place.onegg(pl);
	else 
		player.place.onboard(pl);
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	SRV_ALLP.lookup[pl->c_fd] = pl;
	player.eats(pl);
}

static int32_t	_findteam(t_player *pl)
{
	int32_t		cont;

	if ((cont = team.nameindex(pl->c_fd)) < 0)
		return (0);
	if ((cont = team.addplayer(pl, cont)) < 0)
		return (0);
	return (1);
}

static int32_t	new(int32_t cl)
{
	t_dblist *temp;
	t_player *pl;
	int32_t ret;

	printf("[PLAYER]\n  Creating new player @ : <%d>\n", cl);
	ret = 0;
	if (!(temp = player.pool.pop()))
		return (EXIT_FAILURE);
	pl = (t_player *)temp->data;
	pl->c_fd = cl;
	if (!_findteam(pl))
	{
		client.disconnect(pl->c_fd);
		player.pool.add(pl);
	}
	else
	{
		_initialize(pl);
		graphic.transmit.players.connected(pl);
	}
	return (EXIT_SUCCESS);
}

static int32_t		command(t_player *pl)
{
	if (communication.incoming(pl->c_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	event.lookup(pl->c_fd);
	return (EXIT_SUCCESS);
}

static void eats(t_player *pl)
{
	printf("[PLAYER]\n  Player on : <%p> eats\n", pl);
	event.add(&(eventlookup[EAT]), pl, 0);
}
