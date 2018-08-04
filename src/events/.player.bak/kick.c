/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:37:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 22:13:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "player.h"
#include "graphics.h"
#include "board.h"

static int32_t		kick(void *object);

__attribute__((constructor))void		construct_playercommands_kick(void)
{
	struct s_eventhold	ev9 = {"kick", &kick, 7};

	eventlookup[9] = ev9;
}

static void		_kickplayers(t_player *pl, t_player *og)
{
	char	*num;

	if (pl != og)
	{
		player.place.advance(pl);
		(pl->location.orientation <= 2)  ?
			(num = ft_itoa(pl->location.orientation << 2)) :
			(num = ft_itoa(pl->location.orientation >> 2));
		SENDBUF = strcat(SENDBUF, "moving <");
		SENDBUF = ft_strfreecat(SENDBUF, num);
		SENDBUF = strcat(SENDBUF, ">\n");
		graphic.transmit.players.position(pl);
		bzero(SENDBUF, g_servenv->nsend);
	}
}

static int32_t		kick(void *object)
{
	t_player	*pl;
	t_player	*og;
	int32_t		x;
	int32_t		y;
	t_dblist	*temp;

	og = (t_player *)((t_event *)object)->entity;
	x = og->location.x;
	y = og->location.y;
	temp = PLAYERLIST.first;
	if (temp
		&& temp->data != og)
		communication.outgoing(og->c_fd, "ok\n");
	else
		communication.outgoing(og->c_fd, "ko\n");
	while (temp)
	{
		pl = (t_player *)temp->data;
		_kickplayers(pl, og);
		temp = temp->next;
	}
	SRV_ALLP.status[og->c_fd] = PLAYER;
	bzero(SENDBUF, g_servenv->nsend);
	event.iswaiting(og);
	return (EXIT_SUCCESS);
}
