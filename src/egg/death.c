/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:38:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/15 17:48:41 by nkouris          ###   ########.fr       */
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
	ft_enqueue(death.track.eggs, eg->deathcontainer, 0);
}

static void		now(void)
{
	t_dblist	*temp;
	t_dblist	*deathtemp;
	t_egg		*eg;

	deathtemp = ft_popfirst(death.track.eggs);
	eg = (t_egg *)(deathtemp->data);
	deathtemp = eg->deathcontainer;
	temp = eg->container;
	if ((SRV_TEAM[eg->teamindex]).eggqueue.first->data == (void *)eg)
	{
		(SRV_TEAM[eg->teamindex]).nplayers--;
		ft_popfirst(&((SRV_TEAM[eg->teamindex]).eggqueue));
	}
	bzero(eg, sizeof(t_egg));
	eg->container = temp;
	eg->deathcontainer = deathtemp;
	deathtemp->data = eg;
	egg.pool.add(eg);
	// generate death message to send to graphical client
}

static void		pop(t_egg *eg)
{
	if (death.track.eggs->first
		&& ((void *)eg == death.track.eggs->first->data))
		ft_popfirst(death.track.eggs);
	else if (death.track.eggs->last
			&& ((void *)eg == death.track.eggs->last->data))
		ft_poplast(death.track.eggs);
	else
		ft_dblistpop(eg->deathcontainer);
}
