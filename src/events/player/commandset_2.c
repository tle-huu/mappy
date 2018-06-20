/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandset_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:58:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 01:18:25 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "board.h"
#include "events.h"
#include "communication.h"
#include "inventory.h"
#include "graphics.h"
#include "egg.h"

#define PLX (pl->location.x)
#define PLY (pl->location.y)
# define PL_RESOURCE ((((((SRV_BORD.tiles)[PLX]).column)[PLY]).resources).items)

static int32_t		take(void *object);
static int32_t		right(void *object);
static int32_t		left(void *object);
static int32_t		put(void *object);

__attribute__((constructor))void	construct_playercommands_set2(void)
{
	struct s_eventhold ev4 = {"take", &take, 7};
	struct s_eventhold ev5 = {"right", &right, 7};
	struct s_eventhold ev6 = {"left", &left, 7};
	struct s_eventhold ev7 = {"put", &put, 7};

	eventlookup[4] = ev4;
	eventlookup[5] = ev5;
	eventlookup[6] = ev6;
	eventlookup[7] = ev7;
}

static int32_t		take(void *object)
{
	t_player	*pl;
	char		*message;
	char		*temp;
	int			i;

	pl = (t_player *)((t_event *)object)->entity;
	message = ((t_event *)(object))->message;
	if ((temp = strchr(message, '\n')))
		*temp = '\0';
	i = 0;
	printf("[EVENT]\n  Trying to pickup %s\n", message);
	while (i < NRESOURCES)
	{
		if (ft_strequ(resources[i].name, message))
		{
			if (board.tile.check(pl->location.x, pl->location.y, i))
			{
				inventory.add(&(pl->inventory.items), i);
				inventory.remove(&(PL_RESOURCE), i);
				communication.outgoing(pl->c_fd, "ok\n");
			}
			else
				communication.outgoing(pl->c_fd, "ko\n");
			break ;
		}
		i++;
	}
	if (i == NRESOURCES)
		communication.outgoing(pl->c_fd, "ko\n");
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	event.iswaiting(pl);
	graphic.transmit.players.items(pl);
	return (EXIT_SUCCESS);
}

static int32_t		right(void *object)
{
	t_player	*pl;

	pl = (t_player *)((t_event *)object)->entity;
	if (pl->location.orientation == WEST)
		pl->location.orientation = NORTH;
	else
		pl->location.orientation = pl->location.orientation << 1;
	communication.outgoing(pl->c_fd, "ok\n");
	graphic.transmit.players.position(pl);
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	event.iswaiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t		left(void *object)
{
	t_player	*pl;

	pl = (t_player *)((t_event *)object)->entity;
	if (pl->location.orientation == NORTH)
		pl->location.orientation = WEST;
	else
		pl->location.orientation = pl->location.orientation >> 1;
	communication.outgoing(pl->c_fd, "ok\n");
	graphic.transmit.players.position(pl);
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	event.iswaiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t		put(void *object)
{
	t_player	*pl;
	char		*message;
	char		*temp;
	int			i;

	pl = (t_player *)((t_event *)object)->entity;
	message = ((t_event *)(object))->message;
	if ((temp = strchr(message, '\n')))
		*temp = '\0';
	i = 0;
	while (i < NRESOURCES)
	{
		if (ft_strequ(resources[i].name, message))
		{
			if ((inventory.remove(&(pl->inventory.items), i) == EXIT_FAILURE))
				communication.outgoing(pl->c_fd, "ko\n");
			else
			{
				inventory.add(&(PL_RESOURCE), i);
				communication.outgoing(pl->c_fd, "ok\n");
			}
			break ;
		}
		i++;
	}
	if (i == NRESOURCES)
		communication.outgoing(pl->c_fd, "ko\n");
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	event.iswaiting(pl);
	graphic.transmit.players.items(pl);
	return (EXIT_SUCCESS);
}
