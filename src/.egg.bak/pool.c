/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:31:20 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 23:31:31 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "egg.h"

static int32_t		new(void);
static void			add(t_egg *eg);
static t_dblist		*pop(void);

__attribute__((constructor))void	construct_eggpool(void)
{
	egg.pool.new = &new;
	egg.pool.add = &add;
	egg.pool.pop = &pop;
}

static int32_t		new(void)
{
	t_egg	*eg;
	int32_t	i;
	int32_t	reps;

	i = 0;
	reps = ((MAX_CLIENTS) * (300/42));
	if (!(egg.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(eg = (t_egg *)calloc(1, sizeof(t_egg))))
			return (EXIT_FAILURE);
		eg->container.data = eg;
		eg->deathcontainer.data = eg;
		if (!(ft_enqueue(egg.pool.data, &(eg->container), 0)))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void			add(t_egg *eg)
{
	egg.death.pop(eg);
	bzero(eg, sizeof(t_egg));
	eg->container.data = eg;
	eg->deathcontainer.data = eg;
	ft_enqueue(egg.pool.data, &(eg->container), 0);
	printf("Egg added back to egg pool\n");
}

static t_dblist		*pop(void)
{
	return (ft_popfirst(egg.pool.data));
}
