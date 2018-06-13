/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 13:26:07 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int32_t	new(int32_t cl);
static void		eats(t_player *pl);

__attribute__((constructor))void	construct_playerpool(void)
{
	player.new = &new;
	player.eats = &eats;
}

static int32_t	new(int32_t cl)
{
	t_dblist	*temp;
	t_player	*pl;
	int32_t		ret;
	int32_t		i;
	
	printf("Creating new player <%d>\n", cl);
	ret  = 0;
	i = 0;
	if (!(temp = player.pool.pop()))
		return (EXIT_FAILURE);
	pl = (t_player *)temp->data;
	pl->container = temp;
	pl->c_fd = cl;
	pl->player_id = (SERV_GENV.track_playerid)++;
	(SRV_ALLP.lookup)[cl] = pl;
	while (i++ < 10)
		inventory.ad_food(pl->inventory.items);
	pl.expiration.entity = pl;
	if (player.parse.team(pl) == EXIT_SUCCESS);
		player.eating(pl);
	return (EXIT_SUCCESS);
}

static void		eats(t_player *pl)
{
	event.add(&(commandlookup[EATCOMMAND]), pl, 0);
}
