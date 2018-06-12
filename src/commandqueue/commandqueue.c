/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandqueue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:12:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 21:39:28 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#define CQU_OBJ ((t_command *)(temp->data))

static int32_t	check(void);
static int32_t	addtoqueue(t_command *command);
static int32_t	createpool(void);
static int32_t	addtopool(void);
static t_dblist	*popfrompool(void);

t_commandqueue_methods commandqueue = {
	NULL,
	NULL,
	&check,
	&addtoqueue,
	&createpool,
	&addtopool,
	&popfrompool,
	&popfromqueue
};

static int32_t	createpool(void)
{
	t_command	*temp;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = (MAX_CLIENTS * 10);
	if (!(commandqueue.pool = (t_queue *)calloc(1, sizeof(t_queue)))
		|| !(commandqueue.data = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE);		//error.memory
	while (i < reps)
	{
		if (!(temp = (t_command *)calloc(1, sizeof(t_command)))
			|| !(ft_enqueue(commandqueue.pool, temp, sizeof(t_command))))
			return (EXIT_FAILURE);		//error.memory
		i++;
	}
	return (EXIT_SUCCESS);
}

static int32_t	check(void)
{
	t_dblist	*temp;

	printf("Check time against command queue\n");
	gettimeofday(&(SRV_TIME), NULL);
	if (commandqueue.data->first)
	{
		temp = (commandqueue.data->first);
		while (temp)
		{
			if (server.comparetime(&CQU_OBJ->alarm))
			{
				CQU_OBJ->action(CQU_OBJ->entity);
				temp = commandqueue.popfromqueue();
				commandqueue.addtopool(CQU_OBJ);
			}
			else
				break ;
			temp = (commandqueue.data->first);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t	timeoutsort(t_dblist *one, t_dblist *two)
{
	t_command	*cmdone;
	t_command	*cmdtwo;

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

static int32_t	addtoqueue(t_command *command)
{
	if (!(ft_penqueue(commandqueue.data, command->container, 0, &timeoutsort)))
		return (EXIT_FAILURE); //?? error.memory() ??
	return (EXIT_SUCCESS);
}

static int32_t	addtopool(t_command *command)
{
	t_dblist	*temp;

	temp = command->container;
	bzero(command, sizeof(t_command));
	command->container = temp;
	if (!(ft_enqueue(commandqueue.pool, temp, 0)))
			return (EXIT_FAILURE);		//error.memory
	printf("Nodes available in commandqueue pool : %d\n", (commandqueue.pool)->qlen);
	return (EXIT_SUCCESS);
}

static t_dblist	*popfromqueue(void)
{
	return (ft_popfirst(commandqueue.data));
}

static t_dblist	*popfrompool(void)
{
	return (ft_popfirst(commandqueue.pool));
}
