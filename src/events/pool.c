/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:52:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 21:21:43 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int32_t		new(void);
static t_dblist		*pop_p(void);
static int32_t		add(t_command *command);

__attribute__((constructor))void	construct_eventpool(void)
{
	event.pool.new = &new;
	event.pool.pop = &pop;
	event.pool.add = &add;
}

static int32_t	new(void)
{
	t_command	*temp;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = (MAX_CLIENTS * 10);
	if (!(events.pool.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE);		//error.memory
	while (i < reps)
	{
		if (!(temp = (t_command *)calloc(1, sizeof(t_command)))
			|| !(ft_enqueue(events.pool.data, temp, sizeof(t_command))))
			return (EXIT_FAILURE);		//error.memory
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_dblist	*pop_p(void)
{
	return (ft_popfirst(events.pool.data));
}

static int32_t	add(t_command *command)
{
	t_dblist	*temp;

	temp = command->container;
	bzero(command, sizeof(t_command));
	command->container = temp;
	if (!(ft_enqueue(events.pool.data, temp, 0)))
			return (EXIT_FAILURE);		//error.memory
	printf("Nodes available in events.pool.data : %d\n", (events.pool.data)->qlen);
	return (EXIT_SUCCESS);
}
