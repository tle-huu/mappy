/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:38:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 13:20:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		soon(t_egg *eg);
static void		now(void);

__attribute__((constructor))void	construct_eggdeath(void)
{
	egg.death.soon = &soon;
	egg.death.now = &now;
}

static void		soon(t_egg *eg)
{
	server.setalarm(&(eg->expiration.alarm), 1260);
	ft_enqueue(deathqueue.eggs, eg->deathcontainer, 0);
}

static void		now(void)
{
	t_dblist	*temp;
	t_dblist	*deathtemp;
	t_egg		*eg;

	temp = ft_popfirst(deathqueue.eggs);
	eg = (t_egg *)(temp->data);
	deathtemp = eg->deathcontainer;
	((g_servenv->team)[eg->teamindex])->nplayers--;
	bzero(eg, sizeof(t_egg));
	eg->container = temp;
	eg->deathcontainer = deathtemp;
	eggs.addtopool(eg);
	// generate death message to send to graphical client
}

static void		pop(t_egg *eg)
{
	ft_dblistpop(eg->deathcontainer);
}
