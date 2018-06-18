/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:09:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 21:52:34 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"

static int32_t		all(t_graphic *gr);

__attribute__((constructor))void		construct_transmit_players(void)
{
	graphic.transmit.players.all = &all;
}

static int32_t		_internal_tileloc(t_player *pl)
{
	char	*num;

	num = ft_itoa(pl->location.x);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(pl->location.y);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t		_internal_orientation(t_player *pl)
{
	char	*num;

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

static int32_t		_internal_level(t_player *pl)
{
	char	*num;

	num = ft_itoa(pl->level);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	return (EXIT_SUCCESS);
}

static int32_t		_internal_teamname(t_player *pl)
{
	SENDBUF = strcat(SENDBUF, pl->team->name);
	return (EXIT_SUCCESS);
}

static int32_t		all(t_graphic *gr)
{
	t_player	*pl;
	char		*num;
	int32_t		i;

	i = 0;
	while (i < SRV_SOCK.nfds)
	{
		if (SRV_ALLP.status[i] != GRAPHIC)
		{
			printf("  fuck%d STATUS : %d\n", i, SRV_ALLP.status[i]);
			ft_memset((void *)SENDBUF, 0, 512);
			pl = SRV_ALLP.lookup[i];
			if (!pl)
			{
				i++;
				continue ;
			}
			SENDBUF = strcat(SENDBUF, "pnw ");
			num = ft_itoa((int32_t)(pl->player_id));
			SENDBUF = ft_strfreecat(SENDBUF, num);
			SENDBUF = strcat(SENDBUF, " ");
			_internal_tileloc(pl);
			_internal_orientation(pl);
			_internal_level(pl);
			_internal_teamname(pl);
			SENDBUF = strcat(SENDBUF, "\n");
			communication.outgoing(gr->c_fd, SENDBUF);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
