/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:55:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 12:18:12 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "board.h"
#include "communication.h"
#include "team.h"

/* method function prototypes */
static int32_t	name_exists(int32_t cl);
static int32_t	add_player(int32_t cl, int32_t tm);
static int32_t	send_freespots(int32_t cl);

/* method object */
t_team_methods	team = {
	&name_exists,
	&add_player,
	&send_freespots
};

static int32_t	name_exists(int32_t cl)
{
	t_player	*p;
	int32_t		i;

	i = 0;
	p = (SRV_TEMP.lost)[cl];
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

/*
static int32_t	remove_player(int32_t cl)
{
}

static int32_t	isfull(int32_t cl)
{
}
*/

static int32_t	add_player(int32_t cl, int32_t tm)
{
	t_player	*p;
	t_team		*t;

	printf("Adding player <%d> to |%s|\n", cl, (g_servenv->teams[tm]).name);
	p = SRV_TEMP.lost[cl];
	t = &(g_servenv->teams[tm]);
	p->team = t;
	(p->team->players)[cl] = p;
	SRV_GENV.nclients++;
	SRV_TEMP.lost[cl] = NULL;
	if (team.send_freespots(cl) == EXIT_FAILURE
		|| board.send_dimens(cl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int32_t	send_freespots(int32_t cl)
{
	char		*num;
	char		*str;

	if (!(num = ft_itoa(SRV_GENV.maxclients - SRV_GENV.nclients))
		|| (!(str = calloc(1, strlen(num) + 2)))
		|| (!(str = strcat(str, num)))
		|| (!(str = strcat(str, "\n")))
		|| (communicate.toclient.outgoing(cl, str) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/*
static int32_t	new(int32_t cl)
{
}
*/
