/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:25:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 17:07:42 by nkouris          ###   ########.fr       */
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
			|| (!(temp->expiration = (t_expiration *)calloc(1, sizeof(t_expiration))))
			|| !(ft_enqueue(egg.pool, temp, sizeof(t_egg))))
			return (EXIT_FAILURE); // memory error
		i++;
	}
	return (EXIT_SUCCESS);
}

static void		death(void)
{
	t_dblist	*temp;
	t_egg		*rottenegg;

	temp = ft_popfirst(deathqueue.eggs);
	rottenegg = (t_egg *)((t_expiration *)temp->data)->entity;
	((g_servenv->team)[rottenegg->teamindex])->nplayers--;
	rottenegg->teamindex = -1;
	server.cleartime(&(rottenegg->expiration->alarm));
	rottenegg->expiration->entity = NULL;
	eggs.addtopool(rottenegg);
	// generate death message to send to graphical client
}

static void		addtopool(t_egg *add)
{
	ft_enqueue(egg.pool, add, 0);
	printf("Egg added back to egg pool\n");
}

static int32_t
