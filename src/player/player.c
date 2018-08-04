/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 16:38:57 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "events.h"
#include "board.h"
#include "graphics.h"
#include "client.h"
#include "communication.h"

static int32_t	new (int32_t cl);
static int32_t	command(t_player *pl);

__attribute__((constructor)) void construct_player(void)
{
	player.new = &new;
	player.command = &command;
}

static void		_initialize(t_player *pl)
{
	int32_t i;

	pl->player_id = (SRV_GENV.track_playerid)++;
	pl->tilecontainer.data = pl;
	i = 0;
	player.place.onboard(pl);
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	SRV_ALLP.lookup[pl->c_fd] = pl;
}

static int32_t	new(int32_t cl)
{
	t_dblist	*temp;
	t_player 	*pl;
	int32_t		ret;

	printf("[PLAYER]\n  Creating new player @ : <%d>\n", cl);
	ret = 0;
	if (!(temp = player.pool.pop()))
		return (EXIT_FAILURE);
	pl = (t_player *)temp->data;
	pl->c_fd = cl;
	if ((!SRV_GENV.maxinitial_clients))
	{
		client.disconnect(pl->c_fd);
		player.pool.add(pl);
	}
	else
	{
		_initialize(pl);
		SRV_GENV.connected_vehicles++;
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
