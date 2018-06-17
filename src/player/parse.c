/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:44:32 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 17:44:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"
#include "client.h"
#include "communication.h"
#include "events.h"
#include "team.h"

static int32_t		teamname(t_player *pl);
static int32_t		command(t_player *pl);

__attribute__((constructor))void	construct_playerparse(void)
{
	player.parse.teamname = &teamname;
	player.parse.command = &command;
}


static int32_t		teamname(t_player *pl)
{
	int32_t		ret;
	int32_t		i;

	ret = 0;
	i = 0;
	if ((ret = communication.incoming(pl->c_fd)) == -1)
		return (EXIT_SUCCESS);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((i = team.name_exists(pl->c_fd)) == -1)
	{
		client.disconnect(pl->c_fd);
		return (-1);
	}
	else
	{
		ret = team.add_player(pl, i);
		SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	}
	return (ret);
}

static int32_t		command(t_player *pl)
{
	if (communication.incoming(pl->c_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	event.lookup(pl->c_fd);
	return (EXIT_SUCCESS);
}
