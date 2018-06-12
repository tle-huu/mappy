/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:25:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 22:30:12 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egg.h"

static int32_t		createpool(void);
static void			death(void);
static void			addtopool(t_egg *add);

t_egg_methods	eggs = {
	NULL,
	&createpool,
	&death,
	&addtopool
}

static int32_t		createpool(void)
{
	t_egg	*temp;
	int32_t	i;
	int32_t	reps;

	i = 0;
	reps = ((MAX_CLIENTS) * (300/42));
	if (!(egg.pool = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(temp = (t_egg *)calloc(1, sizeof(t_egg)))
			|| (!(temp->deathcontainer = (t_dblist *)calloc(1, sizeof(t_dblist))))
			|| !(ft_enqueue(egg.pool, temp, sizeof(t_egg))))
			return (EXIT_FAILURE); // memory error
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_dblist		*popfrompool(void)
{
	return (ft_popfirst(egg.pool));
}

static void		addtopool(t_egg *egg)
{
	ft_enqueue(egg.pool, egg->container, 0);
	printf("Egg added back to egg pool\n");
}

static void		transferlocation(t_player *toplayer)
{
	t_dblist	*temp;
	t_team		*tm;
	t_egg		*egg;

	tm = toplayer->team;
	temp = ft_popfirst(tm->eggqueue);
	egg = (t_egg *)temp->data;
	toplayer->location.x = egg->location.x;
	toplayer->location.y = egg->location.y;
	toplayer->location.orientation = egg->location.orientation;
}

static void		death(void)
{
	t_dblist	*temp;
	t_dblist	*deathtemp;
	t_egg		*egg;

	temp = ft_popfirst(deathqueue.eggs);
	egg = (t_egg *)(temp->data);
	deathtemp = egg->deathcontainer;
	((g_servenv->team)[egg->teamindex])->nplayers--;
	bzero(egg, sizeof(t_egg));
	egg->container = temp;
	egg->deathcontainer = deathtemp;
	eggs.addtopool(egg);
	// generate death message to send to graphical client
}

static int32_t	placeonboard(t_egg *egg)
{
	egg->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	egg->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	egg->location.orientation = arc4random_uniform((uint32_t)4);
}
/* coming from the fork command */
static int32_t	incubate(t_player *pl)
{
	t_dblist	*temp;
	t_egg		*egg;

	if (!(temp = egg.popfrompool()))
		return (-1);
	egg = (t_egg *)temp->data;
	egg->container = temp;
	egg->teamindex = pl->teamindex;
	egg->egg_id = SRV_GENV.track_eggid++;
	egg.placeonboard(egg);
	command.add(&(commandlookup[EGGCOMMAND]), egg->container);
}

static int32_t	hatch(void *entity)
{
	t_egg		*egg;
	t_team		*team;

	egg = (t_egg *)entity;
	// add to the queue of eggs available on a team (basically only there
	// for reference as a tile the newly connected client will go to
	team = SRV_TEAM[egg->teamindex];
	team->nplayers++;
	SRV_GENV.maxingame_players++;
	ft_enqueue(team->eggs, egg->deathcontainer, 0);
	egg.impendingdeath(egg);
}

static void		impendingdeath(t_egg *egg)
{
	server.setalarm(&(egg.expiration.alarm), 1260);
	ft_enqueue(deathqueue.eggs, egg->deathcontainer, 0);
}
