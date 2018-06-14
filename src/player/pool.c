/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:27:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 22:37:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "player.h"

static int32_t		new(void);
static t_dblist		*pop(void);
static void			add(t_player *pl);

__attribute__((constructor))void	construct_playerpool(void)
{
	player.pool.new = &new;
	player.pool.pop = &pop;
	player.pool.add = &add;
}

static int32_t		new(void)
{
	t_player	*temp;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = MAX_CLIENTS;
	if (!(player.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(temp = (t_player *)calloc(1, sizeof(t_player)))
			|| !(ft_enqueue(player.pool.data, temp, sizeof(t_player))))
			return (EXIT_FAILURE); // memory error
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_dblist		*pop(void)
{
	return (ft_popfirst(player.pool.data));
}

static void			add(t_player *pl)
{
	ft_enqueue(player.pool.data, pl->container, 0);
}
