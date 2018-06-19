/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:16:32 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 15:42:46 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "death.h"
#include "events.h"
#include "client.h"
#include "graphics.h"
#include "communication.h"
#include "time.h"

static void		soon(t_player *pl);
static void		now(void);

__attribute__((constructor))void	construct_playerdeath(void)
{
	player.death.soon = &soon;
	player.death.now = &now;
}

static void		soon(t_player *pl)
{
	time.setalarm(&(pl->alarm), 0);
	SRV_ALLP.status[pl->c_fd] = DOOMED;
	ft_enqueue(death.track.players, pl->container, 0);
}

static void		now(void)
{
	t_dblist		*temp;
	t_player		*pl;

	temp = ft_popfirst(death.track.players);
	pl = (t_player *)(temp->data);
	if (pl->c_fd)
	{
		// generate death message to send client
		event.removeall((void *)pl);
		communication.outgoing(pl->c_fd, "death\n");
		graphic.transmit.players.death(pl);
		SRV_ALLP.status[pl->c_fd] = DEAD;
		client.disconnect(pl->c_fd);
		player.clear(pl);
		player.pool.add(pl);
	}
}
