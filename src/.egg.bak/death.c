/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:38:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 23:30:28 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "egg.h"
#include "death.h"
#include "time.h"

static void		soon(t_egg *eg);
static void		now(void);
static void		pop(t_egg *eg);

__attribute__((constructor))void	construct_eggdeath(void)
{
	egg.death.soon = &soon;
	egg.death.now = &now;
	egg.death.pop = &pop;
}

static void		soon(t_egg *eg)
{
	time.setalarm(&(eg->alarm), 1260);
	ft_enqueue(death.track.eggs, &(eg->deathcontainer), 0);
}

static void		now(void)
{
	t_dblist	*deathtemp;
	t_egg		*eg;

	deathtemp = ft_popfirst(death.track.eggs);
	eg = (t_egg *)(deathtemp->data);
	if ((SRV_TEAM[eg->teamindex]).eggqueue.first->data == (void *)eg)
	{
		(SRV_TEAM[eg->teamindex]).nplayers--;
		ft_popfirst(&((SRV_TEAM[eg->teamindex]).eggqueue));
	}
	egg.pool.add(eg);
	// generate death message to send to graphical client
}

static void		pop(t_egg *eg)
{
	ft_middel(death.track.eggs, &(eg->deathcontainer));
}
