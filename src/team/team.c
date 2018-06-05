/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:55:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/04 19:05:33 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "team.h"

/* method function prototypes */
static int32_t	name_exists(int32_t client);
static int32_t	add_player(int32_t client, int32_t tm);

/* method object */
t_team_methods	team = {
	&name_exists,
	&add_player
};

static int32_t	name_exists(int32_t client)
{
	t_player	*p;
	int32_t		i;

	i = 0;
	p = (SRV_TEMP.lost)[client];
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
static int32_t	remove_player(int32_t client)
{
}

static int32_t	isfull(int32_t client)
{
}
*/

static int32_t	add_player(int32_t client, int32_t tm)
{
	t_player	*p;
	t_team		*t;

	printf("Adding player <%d> to |%s|\n", client, (g_servenv->teams[tm]).name);
	p = SRV_TEMP.lost[client];
	t = &(g_servenv->teams[tm]);
	p->team = t;
	(p->team->players)[client] = p;
	SRV_GENV.nclients++;
	SRV_TEMP.lost[client] = NULL;
	return (EXIT_SUCCESS);
}

/*
static int32_t	new(int32_t client)
{
}
*/
