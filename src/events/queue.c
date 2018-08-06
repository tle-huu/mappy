/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:48:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:21 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "events.h"
#include "time.h"

#define CQU_OBJ ((t_event *)(temp->data))

static int32_t		new(void);
static int32_t		sort(t_dblist *one, t_dblist *two);
static int32_t		add(t_event *event);
static t_dblist		*pop(void);
static int32_t		check(void);

__attribute__((constructor))void	construct_eventqueue(void)
{
	event.queue.new = &new;
	event.queue.sort = &sort;
	event.queue.add = &add;
	event.queue.pop = &pop;
	event.queue.check = &check;
}

static int32_t	new(void)
{
	if (!(event.queue.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE);	//error.memory
	printf("Event queue created\n");
	return (EXIT_SUCCESS);
}

static int32_t	sort(t_dblist *one, t_dblist *two)
{
	t_event	*cmdone;
	t_event	*cmdtwo;

	cmdone = (t_event *)(one->data);
	cmdtwo = (t_event *)(two->data);
	if (cmdone->alarm.tv_sec < cmdtwo->alarm.tv_sec
		|| ((cmdone->alarm.tv_sec == cmdtwo->alarm.tv_sec)
			&& (cmdone->alarm.tv_usec < cmdtwo->alarm.tv_usec)))
		return (1);
	else if (cmdtwo->alarm.tv_sec < cmdone->alarm.tv_sec
			|| (cmdtwo->alarm.tv_sec == cmdone->alarm.tv_sec
				&& cmdtwo->alarm.tv_usec < cmdone->alarm.tv_usec))
		return (2);
	return (1);
}

static int32_t	add(t_event *ev)
{
	if (!(ft_penqueue(event.queue.data, &(ev->container), 0, event.queue.sort)))
		return (EXIT_FAILURE); //?? error.memory() ??
	return (EXIT_SUCCESS);
}

static t_dblist	*pop(void)
{
	printf("[EVENT]\n  First queue node, pop\n");
	return (ft_popfirst(event.queue.data));
}

static int32_t	check(void)
{
	t_dblist	*temp;

	printf("[EVENT]\n  Check queue\n");
	gettimeofday(&(server.time), NULL);
	if (event.queue.data->first)
	{
		temp = (event.queue.data->first);
		while (temp)
		{
			if (time.compare(&server.time, &CQU_OBJ->alarm))
			{
				printf("  Action\n");
				event.queue.pop();
				CQU_OBJ->action(temp->data);
				event.pool.add(CQU_OBJ);
			}
			else
				break ;
			temp = (event.queue.data->first);
		}
	}
	printf("  No more events ready\n");
	return (EXIT_SUCCESS);
}
