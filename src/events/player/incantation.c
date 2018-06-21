/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 01:09:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 21:25:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "inventory.h"
#include "board.h"

#define UP 1
#define SAME 0

static int32_t	incantation(void *object);
static int32_t	levelup(void *object);

t_sacrifice_required		sacrifice[] = {
	{0, {0,0,0,0,0,0}},
	{1, {0,1,0,0,0,0,0}},	//levelone},
	{2, {0,1,1,1,0,0,0}},	//leveltwo},
	{2, {0,2,0,1,0,2,0}},	//levelthree},
	{4, {0,1,1,2,0,1,0}},	//levelfour},
	{4, {0,1,2,1,3,0,0}},	//levelfive},
	{6, {0,1,2,3,0,1,0}},	//levelsix},
	{6, {0,2,2,2,2,2,1}},	//levelseven},
	{0, {0,0,0,0,0,0}}
};

__attribute__((constructor))void		construct_playercommands_incantation(void)
{
	struct s_eventhold	ev10 = {"incantation", &incantation, 0};
	struct s_eventhold	ev_levelup = {"-- lvlup --", &levelup, 300};

	eventlookup[10] = ev10;
	eventlookup[LVLUP] = ev_levelup;
}

// player levels are checked in reference to pl's requirements
static int32_t	_checkplayers(t_player *og, int32_t x, int32_t y)
{
	t_dblist	*temp;
	t_player	*pl;
	int32_t		req_players;

	req_players = (sacrifice[og->level]).players - 1;
	temp = PLAYERLIST.first;
	while (temp)
	{
		pl = temp->data;
		if (!req_players)
			break ;
		if (pl != og)
		{
			if (pl->level >= og->level)
				req_players--;
		}
		temp = temp->next;
	}
	if (req_players > 0)
		return (0);
	return (1);
}

// resources are checked on a per-player basis
static int32_t	_checkresources(t_player *pl)
{
	int8_t		*req_resources;
	int32_t		i;

	req_resources = (sacrifice[pl->level]).resources;
	i = 0;
	// check and set requirements
	while (i < NRESOURCES)
	{
		if (inventory.check(pl->inventory.items, i) < (int32_t)req_resources[i])
			return (0);
		i++;
	}
	return (1);
}

static int32_t	_sendlevel(int8_t level, t_player *pl)
{
	char	*num;

	if (level)
		(pl->level == 8) ? pl->level : pl->level++;
	SRV_ALLP.status[pl->c_fd] = LEVELING;
	num = ft_itoa(pl->level);
	SENDBUF = strcat(SENDBUF, "current level : ");
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.outgoing(pl->c_fd, SENDBUF);
	//graphical client notification
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t	_commandkickstart(int32_t x, int32_t y)
{
	t_dblist	*temp;
	t_player	*pl;

	temp = PLAYERLIST.first;
	while (temp)
	{
		pl = (t_player *)temp->data;
		if (SRV_ALLP.status[pl->c_fd] == LEVELING)
		{
			pl->priest = 0;
			event.iswaiting(pl);
			temp = temp->next;
			SRV_ALLP.status[pl->c_fd] = PLAYER;
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t	levelup(void *object)
{
	t_dblist	*temp;
	t_player	*pl;
	int32_t		priest;
	int32_t		x;
	int32_t		y;

	pl = (t_player *)((t_event *)object)->entity;
	priest = pl->priest;
	x = pl->location.x;
	y = pl->location.y;
	temp = PLAYERLIST.first;
	while (temp)
	{
		pl = temp->data;
		if (pl->priest == priest)
		{
			if (_checkresources(pl)
				|| _checkplayers(pl, x, y))
				_sendlevel(UP, pl);
			else
				_sendlevel(SAME, pl);
		}
		temp = temp->next;
	}
	_commandkickstart(x, y);
	return (EXIT_SUCCESS);
}

static int32_t	incantation(void *object)
{
	t_dblist	*temp;
	t_player	*pl;
	t_player	*og;
	int32_t		x;
	int32_t		y;

	og = (t_player *)((t_event *)object)->entity;
	x = og->location.x;
	y = og->location.y;
	if (!_checkresources(og)
		|| !_checkplayers(og, x, y))
	{
		communication.outgoing(og->c_fd, "ko\n");
		event.iswaiting(og);
		SRV_ALLP.status[og->c_fd] = PLAYER;
		return (EXIT_SUCCESS);
	}
	communication.outgoing(og->c_fd, "elevation in progress\n");
	SRV_ALLP.status[og->c_fd] = INCANTING;
	og->priest = og->c_fd;
	temp = PLAYERLIST.first;
	while (temp)
	{
		pl = (t_player *)temp->data;
		if (pl != og)
		{
			if (_checkresources(pl)
				|| _checkplayers(pl, x, y))
			{
				communication.outgoing(pl->c_fd, "elevation in progress\n");
				SRV_ALLP.status[pl->c_fd] = INCANTED;
				pl->priest = og->c_fd;
				event.removeall(pl, 1);
			}
		}
		temp = temp->next;
	}
	event.add(&(eventlookup[LVLUP]), pl, 0); 
	return (EXIT_SUCCESS);
}
