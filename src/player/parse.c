/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:44:32 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 14:32:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#define PBUF ((SRV_ALLP.lookup)[cl])->buf

static int32_t		team(t_player *pl);
static int32_t		command(t_player *pl);

__attribute__((constructor))void	construct_playerparse(void)
{
	player.parse.team = &team;
	player.parse.command = &command;
}


static int32_t		team(t_player *pl)
{
	int32_t		ret;
	int32_t		i;

	ret = 0;
	i = 0;
	// add client removal on too many attempts
	if ((ret = communication.incoming(pl->c_fd)) == -1)
		return (EXIT_SUCCESS);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((i = team.name_exists(cl)) == -1)
	{
		client.disconnect(cl);
		return (-1);
	}
	else
	{
		ret = team.add_player(pl, i);
		SRV_ALLP.status[cl] = ACCEPTED;
	}
	return (ret);
}

static int32_t		command(t_player *pl)
{
	char	*firstword_delim;
	char	hold;

	if (communication.incoming(pl->c_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((firstword_delim = strchr(PBUF, ' ')))
	{
		hold = *firstword_delim;
		*firstword_delim = '\0';
	}
	commands.lookup(cl);
	return (EXIT_SUCCESS);
}
