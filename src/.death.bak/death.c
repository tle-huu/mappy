/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:22:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 00:03:46 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "death.h"
#include "vehicle.h"
#include "egg.h"
#include "time.h"

#define TEMP_PLYS ((t_vehicle *)(temp->data))
#define TEMP_EGGS ((t_egg *)(temp->data))

static int32_t		new(void);
static int32_t		check(void);

__attribute__((constructor))void	construct_death(void)
{
	death.track.new = &new;
	death.track.check = &check;
}

static int32_t		new(void)
{
	if (!(death.track.vehicles = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error loop
	if (!(death.track.eggs = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error loop
	return (EXIT_SUCCESS);
}

static int32_t		killvehicle(void)
{
	t_dblist	*temp;

	gettimeofday(&(SRV_RIPT), NULL);
	if (death.track.vehicles)
	{
		temp = (death.track.vehicles->first);
		while (temp)
		{
			if (time.compare(&SRV_RIPT, &(TEMP_PLYS->alarm)))
				vehicle.death.now();
			else
				break ;
			temp = (death.track.vehicles->first);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t		killegg(void)
{
	t_dblist	*temp;

	gettimeofday(&(SRV_RIPT), NULL);
	printf("[DEATH]\n  Egg check\n");
	if (death.track.eggs)
	{
		temp = (death.track.eggs->first);
		while (temp)
		{
			if (time.compare(&(SRV_RIPT), &(TEMP_EGGS->alarm)))
				egg.death.now();
			else
				break ;
			temp = (death.track.eggs->first);
		}
	}
	printf("  Nothing dying\n");
	return (EXIT_SUCCESS);
}

static int32_t		check(void)
{
	printf("Check time against death queues\n");
	killvehicle();
	killegg();
	return (EXIT_SUCCESS);
}
