/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandset_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 22:00:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/18 01:34:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "board.h"

#define Y_AXIS 10
#define X_AXIS -10
static int32_t		see(void *object);

__attribute__((constructor))void		construct_playercommands_set3(void)
{
/*	struct s_eventhold	ev11 = {"kick\n", &kick, 7};
	struct s_eventhold	ev9 = {"broadcast", &broadcast, 7};
	struct s_eventhold	ev10 = {"incantation\n", &incantation, 300}; */
	struct s_eventhold	ev8 = {"see", &see, 7};

	eventlookup[8] = ev8;
/*	eventlookup[9] = ev9;
	eventlookup[10] = ev10;
	eventlookup[11] = ev11;*/
}

/*
north = -y total & -x+x total // smallest to highest
south = +y total & +x-x total // highest to smallest
west = -x total & +y-y total
east = +x total & -y+y total
*/

static int32_t		see_sendstr(t_player *pl)
{
	printf("  I see: |%s|\n", SENDBUF);
	SENDBUF = strcat(SENDBUF, "}\n");
	communication.outgoing(pl->c_fd, SENDBUF);
	SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	event.is_waiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t		see_buildresourcestr(int32_t x, int32_t y)
{
	int32_t		nresource;
	int32_t		nfill;
	int32_t		i;

	if (SENDBUF)
		nfill = strlen(SENDBUF);
	i = 0;
	if (x > SRV_BORD.x)
		x = x - (SRV_BORD.x + 1);
	if (y > SRV_BORD.y)
		y = y - (SRV_BORD.y + 1);
	if (x < 0)
		x = x + SRV_BORD.x;
	if (y < 0)
		y = y + SRV_BORD.y;
	while (i < NRESOURCES)
	{
		nresource = board.tile.check(x, y, i);
		printf("  At (%d, %d)\n  There is : %d %s\n", x, y, nresource, resources[i].name);
		if (nresource)
		{
			nfill = (nfill + sizeof(", ") + (nresource * sizeof(resources[i].name)));
			if (!(SENDBUF) || (nfill > g_servenv->nsend))
			{
				if (!(SENDBUF = (char *)realloc(SENDBUF, nfill)))
					return (EXIT_FAILURE);
				g_servenv->nsend = nfill;
			}
			while (nresource--)
			{
				printf("  go resource\n");
				SENDBUF = strcat(SENDBUF, resources[i].name);
				SENDBUF = strcat(SENDBUF, " ");
			}
		}
		i++;
	}
	printf("  SENDBUF : |%s|\n", SENDBUF);
	return (EXIT_SUCCESS);
}

static int32_t		see_buildplayerstr(int32_t x, int32_t y, t_player *pl)
{
	t_dblist	*temp;
	int32_t		nfill;

	nfill = 0;
	printf("  this is x in seebuildplayer : %d\n  this is y in seebuildplayer : %d\n", x, y);
	if (x > SRV_BORD.x)
		x = x - (SRV_BORD.x + 1);
	if (y > SRV_BORD.y)
		y = y - (SRV_BORD.y + 1);
	if (x < 0)
		x = x + SRV_BORD.x;
	if (y < 0)
		y = y + SRV_BORD.y;
	printf("  this is x in seebuildplayer : %d\n  this is y in seebuildplayer : %d\n", x, y);
	temp = PLAYERLIST.first;
	printf("  go\n");
	while (temp)
	{
		printf("  finding players\n");
		if (temp->data != (void *)pl)
		{
			printf("  found one\n");
			nfill += sizeof("player");
			if (!SENDBUF || (nfill > g_servenv->nsend))
			{
				if (!(SENDBUF = (char *)realloc(SENDBUF, nfill)))
					return (EXIT_FAILURE);
			}
			SENDBUF = strcat(SENDBUF, "player ");
		}
		temp = temp->next;
	}
	g_servenv->nsend += nfill;
	printf("  SENDBUF Players : |%s|\n", SENDBUF);
	return (EXIT_SUCCESS);
}

static int32_t		see_zeroblock(t_player *pl)
{
	int32_t	x;
	int32_t	y;

	x = pl->location.x;
	y = pl->location.y;
	bzero(SENDBUF, g_servenv->nsend);
	SENDBUF = strcat(SENDBUF, "{ ");
	if (!SENDBUF)
	{
		if (!(SENDBUF = (char *)calloc(1, 3)))
			return (EXIT_FAILURE);
		g_servenv->nsend = 3;
	}
	if (see_buildplayerstr(x, y, pl) == EXIT_FAILURE
		|| see_buildresourcestr(x, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	SENDBUF = strcat(SENDBUF, ", ");
	return (EXIT_SUCCESS);
}

static int32_t		see(void *object)
{
	t_player	*pl;
	int32_t		mainline;
	int32_t		maintrans;
	int32_t		perptrans;
	int32_t		perpaxis;
	int32_t		x;
	int32_t		y;
	int32_t		i;
	int32_t		j;

	pl = (t_player *)((t_event *)object)->entity;
	(pl->location.orientation & (NORTH | SOUTH)) ? (mainline = Y_AXIS) :
		(mainline = X_AXIS);
	(pl->location.orientation & (NORTH | EAST)) ? (maintrans = -1) :
		(maintrans = 1);
	(pl->location.orientation & (NORTH | EAST)) ? (perptrans = -1) :
		(perptrans = 1);
	printf("[SEE]\n");
	if (see_zeroblock(pl) == EXIT_FAILURE)
	{
		printf("  Zeroblock failed\n");
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i <= pl->level)
	{
		(mainline == Y_AXIS) ? (perpaxis = pl->location.x + (perptrans * i)) :
			(perpaxis = pl->location.y + (perptrans * i));
		(mainline == Y_AXIS) ? (y = pl->location.y + (maintrans * i)) :
			(x = pl->location.x + (maintrans * i));
		j = 0;
		while (j < (1 + (i * 2)))
		{
			if (perpaxis < 0)
			{
				(mainline == Y_AXIS) ? (x = (SRV_BORD.x + perpaxis)) :
					(y = (SRV_BORD.y + perpaxis));
			}
			else if ((mainline == Y_AXIS) && (perpaxis > SRV_BORD.x))
				x = (perpaxis - SRV_BORD.x);
			else if ((mainline == X_AXIS) && (perpaxis > SRV_BORD.y))
				y = (perpaxis - SRV_BORD.y);
			else
				(mainline == Y_AXIS) ? (x = perpaxis) :
					(y = perpaxis);
			pl->location.orientation & (NORTH | EAST) ? perpaxis++ : perpaxis--;
			see_buildplayerstr(x, y, pl);
			see_buildresourcestr(x, y);
			if (i != pl->level || j != ((1 + (i * 2)) - 1))
				SENDBUF = strcat(SENDBUF, ", ");
			j++;
		}
		i++;
	}
	see_sendstr(pl);
	return (EXIT_SUCCESS);
}
