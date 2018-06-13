/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:55:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 14:41:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/* method function prototypes */
static int32_t	name_exists(int32_t cl);
static int32_t	add_player(int32_t cl, int32_t tm);
static int32_t	send_freespots(int32_t cl, int32_t tm);

__attribute__((constructor))void	construct_team(void)
{
	team.name_exists = &name_exists;
	team.add_player = &add_player;
	team.send_freespots = &send_freespots;
}

static int32_t	name_exists(int32_t cl)
{
	t_player	*p;
	int32_t		i;

	i = 0;
	p = (SRV_ALLP.lookup)[cl];
	printf("Player <%d> requesting to be on team |%s|\n", p->c_fd, p->buf);
	while ((i < SRV_GENV.nteams))
	{
		printf("team |%s|\n", (g_servenv->teams[i]).name);
		if ((ft_strequ(p->buf, (g_servenv->teams[i]).name)))
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
		(tm->players)[cl] = pl;
		SRV_GENV.maxinitial_clients ? SRV_GENV.maxclients-- : 0;
		SRV_GENV.maxingame_players--;
		tm->nplayers--;
		if (tm->eggqueue)
			player.place.onegg(pl);
		else 
			player.placeonboard(cl);
		printf("Adding player <%d> to |%s|\n", cl, tm.name);
		if ((team.send_freespots(cl, tm) == EXIT_FAILURE)
			|| (board.send_dimensions(cl) == EXIT_FAILURE))
			return (EXIT_FAILURE);
	}
	else
	{
		printf("player <%d> tried to join |%s|,no room\n", cl, tm.name);
		client.disconnect(cl);
	}
	return (EXIT_SUCCESS);
}

static int32_t	send_freespots(int32_t cl, t_team *tm)
{
	char		*num;
	char		*str;

	if (!(num = ft_itoa(tm.nplayers)
		|| (!(str = calloc(1, strlen(num) + 2)))
		|| (!(str = ft_strfreecat(str, num)))
		|| (!(str = strcat(str, "\n")))
		|| (communication.outgoing(cl, str) == EXIT_FAILURE)))
		return (EXIT_FAILURE);
	free(str);
	return (EXIT_SUCCESS);
}
