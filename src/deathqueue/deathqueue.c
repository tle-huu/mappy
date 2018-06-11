/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:06:05 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 17:07:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "death.h"

#define EXP_OBJ ((t_expiration *)(exp->data))
#define EXP_PLYS ((t_player *)((EXP_OBJ)->entity))
#define EXP_EGGS ((t_egg *)((EXP_OBJ)->entity))

static int32_t		check(void);
static int32_t		player(void);
static int32_t		egg(void);

t_deathqueue	deathqueue = {
	NULL,
	NULL,
	&check,
	&player,
	&egg
}

static int32_t		new(void)
{
	if (!(deathqueue.players = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error loop
	if (!(deathqueue.eggs = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error loop
}

static int32_t		check(void)
{
	printf("Check time against death queues\n");
	deathqueue.player();
	deathqueue.egg();
}

static int32_t		player(void)
{
	t_dblist	*exp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (deathqueue.players)
	{
		exp = (deathqueue.players->first);
		while (expiration)
		{
			if (server.comparetime(&EXP_OBJ->alarm))
				player.death();
			else
				break ;
			exp = (deathqueue.players->first);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t		egg(void)
{
	t_dblist	*exp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (deathqueue.eggs)
	{
		exp = (deathqueue.eggs->first);
		while (expiration)
		{
			if (server.comparetime(&EXP_OBJ->alarm))
				egg.death();
			else
				break ;
			exp = (deathqueue.eggs->first);
		}
	}
	return (EXIT_SUCCESS);
}
