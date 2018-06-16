/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:55:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/15 21:14:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "team.h"
#include "player.h"
#include "board.h"
#include "client.h"
#include "communication.h"

static int32_t	name_exists(int32_t cl);
static int32_t	add_player(t_player *pl, int32_t tm);
static int32_t	send_freespots(int32_t cl, t_team *tm);

__attribute__((constructor))void	construct_team(void)
{
	team.name_exists = &name_exists;
	team.add_player = &add_player;
	team.send_freespots = &send_freespots;
}

static int32_t	name_exists(int32_t cl)
{
	t_player	*pl;
	int32_t		i;
	char		*temp;

	i = 0;
	pl = SRV_ALLP.lookup[cl];
	printf("Player <%d> requesting to be on team |%s|\n", pl->c_fd, RECVBUF);
	if ((temp = strchr(RECVBUF, '\n')))
		*temp = '\0';
	while ((i < SRV_GENV.nteams))
	{
		printf("team |%s|\n", (g_servenv->teams[i]).name);
		if ((ft_strequ(RECVBUF, (g_servenv->teams[i]).name)))
			break ;
		i++;
	}
	if (i == SRV_GENV.nteams)
		return (-1);
	return (i);
}

static int32_t	add_player(t_player *pl, int32_t teamindex)
{
	t_team		*tm;

	tm = &(g_servenv->teams[teamindex]);
	if (tm->nplayers)
	{
		pl->team = tm;
		(tm->players)[pl->c_fd] = pl;
		SRV_GENV.maxinitial_clients ? SRV_GENV.maxinitial_clients-- : 0;
		SRV_GENV.maxingame_players--;
		tm->nplayers--;
		if (tm->eggqueue.first)
			player.place.onegg(pl);
		else 
			player.place.onboard(pl);
		printf("Adding player <%d> to |%s|\n", pl->c_fd, tm->name);
		if ((team.send_freespots(pl->c_fd, tm) == EXIT_FAILURE)
			|| (board.send_dimensions(pl->c_fd) == EXIT_FAILURE))
			return (EXIT_FAILURE);
	}
	else
	{
		printf("player <%d> tried to join |%s|,no room\n", pl->c_fd, tm->name);
		client.disconnect(pl->c_fd);
	}
	return (EXIT_SUCCESS);
}

static int32_t	send_freespots(int32_t cl, t_team *tm)
{
	char		*num;
	char		*str;

	num = NULL;
	if (!(num = ft_itoa(tm->nplayers))
		|| (!(str = calloc(1, strlen(num) + 2)))
		|| (!(str = ft_strfreecat(str, num)))
		|| (!(str = strcat(str, "\n")))
		|| (communication.outgoing(cl, str) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	free(str);
	return (EXIT_SUCCESS);
}
