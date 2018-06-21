/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eggs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:41:29 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/21 12:57:52 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "graphics.h"
#include "communication.h"

static int32_t		all(t_graphic *gr);
static int32_t		one(t_egg *eg);

__attribute__((constructor)) void construct_transmit_eggs(void)
{
	graphic.transmit.eggs.all = &all;
	graphic.transmit.eggs.one = &one;
}

static void			_eggid(t_egg *eg)
{
	char	*num;

	num = ft_itoa((int32_t)eg->egg_id);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(eg->progenitor);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
}

static void			_tileloc(t_egg *eg)
{
	char *num;

	num = ft_itoa(eg->location.x);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(eg->location.y);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
}

static int32_t		one(t_egg *eg)
{
	SENDBUF = strcat(SENDBUF, "enw ");
	_eggid(eg);
	_tileloc(eg);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.graphical(NULL, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t		all(t_graphic *gr)
{
	t_dblist	*temp;
	t_egg		*eg;
	int32_t		i;

	i = 0;
	while (i < SRV_GENV.nteams)
	{
		temp = SRV_TEAM[i].eggqueue.first;
		while (temp)
		{
			SENDBUF = strcat(SENDBUF, "enw ");
			_eggid(eg);
			eg = (t_egg *)(temp)->data;
			_tileloc(eg);
			SENDBUF = strcat(SENDBUF, "\n");
			communication.graphical(gr, SENDBUF);
			bzero(SENDBUF, g_servenv->nsend);
			temp = temp->next;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
