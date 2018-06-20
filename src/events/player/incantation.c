/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 01:09:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 02:12:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "board.h"

static int32_t	incantation(void *object);

__attribute__((constructor))void		construct_playercommands_see(void)
{
	struct s_resource_sacrifice	levelone = {0,1,0,0,0,0,0};
	struct s_resource_sacrifice	leveltwo = {0,1,1,1,0,0,0};
	struct s_resource_sacrifice	levelthree = {0,2,0,1,0,2,0};
	struct s_resource_sacrifice	levelfour = {0,1,1,2,0,1,0};
	struct s_resource_sacrifice	levelfive = {0,1,2,1,3,0,0};
	struct s_resource_sacrifice	levelsix = {0,1,2,3,0,1,0};
	struct s_resource_sacrifice	levelseven = {0,2,2,2,2,2,1};

	struct s_sacrifice_required		sacrifice[8] = {
		NULL,
		{1, levelone},
		{2, leveltwo},
		{2, levelthree},
		{4, levelfour},
		{4, levelfive},
		{6, levelsix},
		{6, levelseven},
		NULL
	}

	struct s_eventhold	ev10 = {"incantation\n", &incantation, 300};

	eventlookup[9] = ev9;
}

static int32_t	_checkplayers(t_player *pl, int32_t x, int32_t y)
{
}

static int32_t	_checkresources(t_player *pl, int32_t x, int32_t y)
{
	t_player	*temp;
	int8_t		*req_resources;

	// check and set requirements
	while (
}

static int32_t	levelup(void *object)
{
	t_player	*pl;

	// check resources
	// check players and status flags
	// adjust levels
	// send responses
}

static int32_t	incantation(void *object)
{
	t_player	*pl;
	t_player	*og;
	int32_t		x;
	int32_t		y;

	x = og->location.x;
	y = og->location.y;
	if (_checkresources(og) < 0
		|| _checkplayers(og) < 0)
	{
		communication.outgoing(og->c_fd, "ko\n");
		return (EXIT_SUCCESS);
	}
	communication.outgoing(pl->c_fd, "elevation in progress\n");
	SRV_ALLP.status[pl->c_fd] = INCANTING;
	pl = PLAYERLIST->first;
	while (pl)
	{
		if (pl != og)
		{
			if (_checkresources(pl) == EXIT_SUCCESS
				|| _checkplayers(pl) == EXIT_SUCCESS)
			{
				communication.outgoing(pl->c_fd, "elevation in progress\n");
				SRV_ALLP.status[pl->c_fd] = INCANTED;
			}
		}
		pl = pl->tilecontainer.next;
	}
	event.add(&(eventlookup[LEVELUP]), pl, 0); 
	return (EXIT_SUCCESS);
}
