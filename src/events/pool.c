/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:52:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 13:17:28 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"

static int32_t		new(void);
static t_dblist		*pop(void);
static void			add(t_event *ev);

__attribute__((constructor))void	construct_eventpool(void)
{
	event.pool.new = &new;
	event.pool.pop = &pop;
	event.pool.add = &add;
}

static int32_t	new(void)
{
	t_event		*temp;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = (MAX_CLIENTS * 10);
	if (!(event.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE);		//error.memory
	printf("[EVENT]\n  -- Creating event pool --\n");
	while (i < reps)
	{
		if (!(temp = (t_event *)calloc(1, sizeof(t_event)))
			|| !(ft_enqueue(event.pool.data, temp, sizeof(t_event))))
			return (EXIT_FAILURE);		//error.memory
		i++;
	}
	printf("  Event pool created\n");
	return (EXIT_SUCCESS);
}

static t_dblist	*pop(void)
{
	return (ft_popfirst(event.pool.data));
}

static void		add(t_event *ev)
{
	t_dblist	*temp;

	temp = ev->container;
	bzero(ev, sizeof(t_event));
	ev->container = temp;
	ft_enqueue(event.pool.data, temp, 0);
	printf("Nodes available in events.pool.data : %d\n", (event.pool.data)->qlen);
}
