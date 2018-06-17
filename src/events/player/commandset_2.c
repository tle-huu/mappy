/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandset_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:58:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 17:27:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "board.h"
#include "events.h"
#include "communication.h"
#include "inventory.h"
#include "egg.h"

#define PLX (pl->location.x)
#define PLY (pl->location.y)
# define PL_RESOURCE ((((((SRV_BORD.tiles)[PLX]).column)[PLY]).resources).items)

static int32_t		take(void *object);

__attribute__((constructor))void	construct_playercommands_set2(void)
{
	struct s_eventhold ev4 = {"take", &take, 7};
//	struct s_eventhold ev5 = {"right\n", , 42};
//	struct s_eventhold ev6 = {"left\n", , 0};
//	struct s_eventhold ev7 = {"see\n", , 1};

	eventlookup[4] = ev4;
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
	SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	event.is_waiting(pl);
	return (EXIT_SUCCESS);
}
