/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:38:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 17:36:44 by nkouris          ###   ########.fr       */
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
	time.setalarm(&(eg->expiration.alarm), 1260);
	ft_enqueue(death.track.eggs, eg->deathcontainer, 0);
}

static void		now(void)
{
	t_dblist	*temp;
	t_dblist	*deathtemp;
	t_egg		*eg;

	temp = ft_popfirst(death.track.eggs);
	eg = (t_egg *)(temp->data);
	deathtemp = eg->deathcontainer;
	((g_servenv->teams)[eg->teamindex]).nplayers--;
	bzero(eg, sizeof(t_egg));
	eg->container = temp;
	eg->deathcontainer = deathtemp;
	egg.pool.add(eg);
	// generate death message to send to graphical client
}

static void		pop(t_egg *eg)
{
	ft_dblistpop(eg->deathcontainer);
}
