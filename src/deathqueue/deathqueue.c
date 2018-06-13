/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:06:05 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 10:31:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "death.h"

#define TEMP_PLYS ((t_player *)(temp->data))
#define TEMP_EGGS ((t_egg *)(temp->data))

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
	t_dblist	*temp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (deathqueue.players)
	{
		temp = (deathqueue.players->first);
		while (temp)
		{
			if (time.compare(&(TEMP_PLY.expiration.alarm)))
				player.death();
			else
				break ;
			temp = (deathqueue.players->first);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t		egg(void)
{
	t_dblist	*temp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (deathqueue.eggs)
	{
		temp = (deathqueue.eggs->first);
		while (temp)
		{
			if (time.compare(&temp_OBJ->alarm))
				egg.death();
			else
				break ;
			temp = (deathqueue.eggs->first);
		}
	}
	return (EXIT_SUCCESS);
}
