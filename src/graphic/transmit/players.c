/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:41:24 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 15:41:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"

static int32_t all(t_graphic *gr);
static int32_t items(t_player *pl);
static int32_t position(t_player *pl);
static int32_t connected(t_player *pl);
static int32_t death(t_player *pl);

__attribute__((constructor)) void construct_transmit_players(void)
{
	graphic.transmit.players.all = &all;
	graphic.transmit.players.items = &items;
	graphic.transmit.players.position = &position;
	graphic.transmit.players.connected = &connected;
	graphic.transmit.players.death = &death;
}

static int32_t _internal_tileloc(t_player *pl)
{
	char *num;

	num = ft_itoa(pl->location.x);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(pl->location.y);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t _internal_orientation(t_player *pl)
{
	char *num;

	num = NULL;
	if (pl->location.orientation & NORTH)
		num = ft_itoa(1);
	else if (pl->location.orientation & EAST)
		num = ft_itoa(2);
	else if (pl->location.orientation & SOUTH)
		num = ft_itoa(3);
	else if (pl->location.orientation & WEST)
		num = ft_itoa(4);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t _internal_level(t_player *pl)
{
	char *num;

	num = ft_itoa(pl->level);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t _internal_teamname(t_player *pl)
{
	SENDBUF = strcat(SENDBUF, pl->team->name);
	return (EXIT_SUCCESS);
}

static int32_t _internal_inventory(t_player *pl)
{
	char *num;

	num = ft_itoa(FOOD(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(LINEMATE(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(SIBUR(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(DERAUMERE(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(MENDIANE(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(PHIRAS(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(THYSTAME(pl->inventory.items));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	return (EXIT_SUCCESS);
}
/* :> player_position
	- Send the players individual position to the graphic clients.
*/
static int32_t position(t_player *pl)
{
	char *num;

	SENDBUF = strcat(SENDBUF, "ppo ");
	num = ft_itoa((int32_t)pl->player_id);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	_internal_tileloc(pl);
	_internal_orientation(pl);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

/* :> player_connected
	- Send the new players init message to the graphics client.
*/
static int32_t connected(t_player *pl)
{
	char *num;

	SENDBUF = strcat(SENDBUF, "pnw ");
	num = ft_itoa((int32_t)(pl->player_id));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	_internal_tileloc(pl);
	_internal_orientation(pl);
	_internal_level(pl);
	_internal_teamname(pl);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t	death(t_player *pl)
{
	char *num;

	SENDBUF = strcat(SENDBUF, "pdi ");
	num = ft_itoa((int32_t)(pl->player_id));
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t items(t_player *pl)
{
	char *num;

	SENDBUF = strcat(SENDBUF, "pin ");
	num = ft_itoa((int32_t)pl->player_id);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	_internal_tileloc(pl);
	_internal_inventory(pl);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t all(t_graphic *gr)
{
	t_player *pl;
	char *num;
	int32_t i;

	i = 0;
	while (i < SRV_SOCK.nfds)
	{
		if (SRV_ALLP.status[i] != GRAPHIC
			&& SRV_ALLP.lookup[i])
		{
			pl = SRV_ALLP.lookup[i];
			SENDBUF = strcat(SENDBUF, "pnw ");
			num = ft_itoa((int32_t)(pl->player_id));
			SENDBUF = ft_strfreecat(SENDBUF, num);
			SENDBUF = strcat(SENDBUF, " ");
			_internal_tileloc(pl);
			_internal_orientation(pl);
			_internal_level(pl);
			_internal_teamname(pl);
			SENDBUF = strcat(SENDBUF, "\n");
			communication.graphical(gr, SENDBUF);
			bzero(SENDBUF, g_servenv->nsend);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
