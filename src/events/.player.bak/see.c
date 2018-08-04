/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 15:12:32 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/25 11:51:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "board.h"

#define Y_AXIS 10
#define X_AXIS -10

static int32_t		see(void *object);

__attribute__((constructor))void		construct_playercommands_see(void)
{
	struct s_eventhold	ev8 = {"see", &see, 7};

	eventlookup[8] = ev8;
}

/*
north = -y total & -x+x total // smallest to highest
south = +y total & +x-x total // highest to smallest
west = -x total & +y-y total
east = +x total & -y+y total
*/

static void		_boardwrap(int32_t *x, int32_t *y)
{
	if (*x > SRV_BORD.x)
		*x = *x - (SRV_BORD.x + 1);
	if (*y > SRV_BORD.y)
		*y = *y - (SRV_BORD.y + 1);
	if (*x < 0)
		*x = *x + SRV_BORD.x;
	if (*y < 0)
		*y = *y + SRV_BORD.y;
}

static int32_t		_sendstr(t_player *pl)
{
	printf("  I see: |%s|\n", SENDBUF);
	SENDBUF = strcat(SENDBUF, "}\n");
	communication.outgoing(pl->c_fd, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	SRV_ALLP.status[pl->c_fd] = PLAYER;
	event.iswaiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t		_buildresourcestr(int32_t x, int32_t y)
{
	int32_t		nresource;
	int32_t		nfill;
	int32_t		i;

	nfill = strlen(SENDBUF);
	_boardwrap(&x, &y);
	i = 0;
	while (i < NRESOURCES)
	{
		nresource = board.tile.check(x, y, i);
		if (nresource)
		{
			nfill = (nfill + sizeof(", }\n") + (nresource * sizeof(resources[i].name)));
			if (!(SENDBUF) || (nfill > g_servenv->nsend))
			{
				if (!(SENDBUF = (char *)realloc(SENDBUF, nfill)))
					return (EXIT_FAILURE);
				g_servenv->nsend = nfill;
			}
			while (nresource--)
			{
				SENDBUF = strcat(SENDBUF, resources[i].name);
				SENDBUF = strcat(SENDBUF, " ");
			}
		}
		i++;
	}
	printf("  SENDBUF : |%s|\n", SENDBUF);
	return (EXIT_SUCCESS);
}

static int32_t		_buildplayerstr(int32_t x, int32_t y, t_player *pl)
{
	t_dblist	*temp;
	int32_t		nfill;

	nfill = 0;
	_boardwrap(&x, &y);
	temp = PLAYERLIST.first;
	while (temp)
	{
		printf("  finding players\n");
		if (temp->data != (void *)pl)
		{
			printf("  found one\n");
			nfill += sizeof("player");
			if (!SENDBUF || (nfill > g_servenv->nsend))
			{
				printf(" REALLOC CALL\n");
				if (!(SENDBUF = (char *)realloc(SENDBUF, nfill)))
					return (EXIT_FAILURE);
				g_servenv->nsend += nfill;
			}
			SENDBUF = strcat(SENDBUF, "player ");
		}
		temp = temp->next;
	}
	printf("  SENDBUF Players : |%s|\n", SENDBUF);
	return (EXIT_SUCCESS);
}

static int32_t		_zeroblock(t_player *pl)
{
	int32_t	x;
	int32_t	y;

	x = pl->location.x;
	y = pl->location.y;
	bzero(SENDBUF, g_servenv->nsend);
	SENDBUF = strcat(SENDBUF, "{");
	if (_buildplayerstr(x, y, pl) == EXIT_FAILURE
		|| _buildresourcestr(x, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!SENDBUF[1])
		SENDBUF = strcat(SENDBUF, " ,");
	else
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
	_zeroblock(pl);
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
			_buildplayerstr(x, y, pl);
			_buildresourcestr(x, y);
			if (i != pl->level || j != ((1 + (i * 2)) - 1))
			{
				if (i == 1 && SENDBUF[2] == ',')
					SENDBUF = strcat(SENDBUF, " , ");
				else
					SENDBUF = strcat(SENDBUF, ", ");
			}
			j++;
		}
		i++;
	}
	_sendstr(pl);
	return (EXIT_SUCCESS);
}
