/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:14:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 11:14:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "death.h"

#define TEMP_PLYS ((t_player *)(temp->data))
#define TEMP_EGGS ((t_egg *)(temp->data))

static int32_t		new(void);
static int32_t		check(void);

__attribute__((constructor))void	construct_death.track.void)
{
	death.track.new = &new;
	death.track.check = &check;
}

static int32_t		new(void)
{
	if (!(death.track.players = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error loop
	if (!(death.track.eggs = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error loop
}

static int32_t		player(void)
{
	t_dblist	*temp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (death.track.players)
	{
		temp = (death.track.players->first);
		while (temp)
		{
			if (time.compare(&(TEMP_PLY.expiration.alarm)))
				player.death();
			else
				break ;
			temp = (death.track.players->first);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t		egg(void)
{
	t_dblist	*temp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (death.track.eggs)
	{
		temp = (death.track.eggs->first);
		while (temp)
		{
			if (time.compare(&temp_OBJ->alarm))
				egg.death();
			else
				break ;
			temp = (death.track.eggs->first);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t		check(void)
{
	printf("Check time against death queues\n");
	player();
	egg();
}
