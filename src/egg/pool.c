/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:31:20 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 18:01:39 by nkouris          ###   ########.fr       */
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
	t_egg	*temp;
	int32_t	i;
	int32_t	reps;

	i = 0;
	reps = ((MAX_CLIENTS) * (300/42));
	if (!(egg.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(temp = (t_egg *)calloc(1, sizeof(t_egg)))
			|| (!(temp->deathcontainer = (t_dblist *)calloc(1, sizeof(t_dblist)))))
			return (EXIT_FAILURE); // memory error
		temp->deathcontainer->data = temp;
		if (!(ft_enqueue(egg.pool.data, temp, sizeof(t_egg))))
			return (EXIT_FAILURE); // memory error
		i++;
	}
	return (EXIT_SUCCESS);
}

static void			add(t_egg *eg)
{
	t_dblist	*temp;

	temp = eg->container;
	bzero(eg, sizeof(t_egg));
	eg->container = temp;
	// pop egg from death queue as well!
	ft_enqueue(egg.pool.data, eg->container, 0);
	printf("Egg added back to egg pool\n");
}

static t_dblist		*pop(void)
{
	return (ft_popfirst(egg.pool.data));
}
