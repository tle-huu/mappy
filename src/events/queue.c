/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:48:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 22:15:28 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sever.h"

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
}

static int32_t	sort(t_dblist *one, t_dblist *two)
{
	t_event	*cmdone;
	t_event	*cmdtwo;

	cmdone = one->data;
	cmdtwo = two->data;
	if (cmdone->alarm.tv_sec < cmdtwo->alarm.tv_sec
		|| (cmdone->alarm.tv_sec == cmdtwo->alarm.tv_sec
			&& cmdone->alarm.tv_usec < cmdone->alarm.tv_usec))
		return (1);
	else if (cmdtwo->alarm.tv_sec < cmdtwo->alarm.tv_sec
			|| (cmdtwo->alarm.tv_sec == cmdtwo->alarm.tv_sec
				&& cmdtwo->alarm.tv_usec < cmdtwo->alarm.tv_usec))
		return (2);
	return (1);
}

static int32_t	add(t_event *event)
{
	if (!(ft_penqueue(event.pool.data, event->container, 0, &event.queue.sort)))
		return (EXIT_FAILURE); //?? error.memory() ??
	return (EXIT_SUCCESS);
}

static t_dblist	*pop(void)
{
	return (ft_popfirst(event.queue.data));
}

static int32_t	check(void)
{
	t_dblist	*temp;

	printf("Check time against event queue\n");
	gettimeofday(&(SRV_TIME), NULL);
	if (event.pool.data->first)
	{
		temp = (event.pool.data->first);
		while (temp)
		{
			if (time.compare(&CQU_OBJ->alarm))
			{
				CQU_OBJ->action(CQU_OBJ->entity);
				temp = event.queue.pop_q();
				event.pool.add_p(CQU_OBJ);
			}
			else
				break ;
			temp = (event.pool.data->first);
		}
	}
	return (EXIT_SUCCESS);
}
