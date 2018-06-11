/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandqueue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:12:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 15:01:01 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "commandqueue.h"

#define CQU_OBJ ((t_command *)(cmd->data))

static int32_t	check(void);
static int32_t	addtoqueue(t_dblist *command);
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
	&popfrompool
};

static int32_t	check(void)
{
	t_dblist	*cmd;

	printf("Check time against command queue\n");
	gettimeofday(&(SRV_TIME), NULL);
	if (commandqueue.data)
	{
		cmd = (commandqueue.data->first);
		while (cmd)
		{
			if (server.comparetime(&CQU_OBJ->alarm))
			{
				CQU_OBJ->action(CQU_OBJ->player);
				commandqueue.addtopool();
			}
			else
				break ;
			cmd = (commandqueue.data->first);
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

static int32_t	addtoqueue(t_dblist *command)
{
	if (!(ft_penqueue(commandqueue.data, command, 0, &timeoutsort)))
		return (EXIT_FAILURE); //?? error.memory() ??
	return (EXIT_SUCCESS);
}

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

static int32_t	addtopool(void)
{
	t_dblist	*cmd;

	cmd = ft_popfirst(commandqueue.data);
	server.cleartime(&(CQU_OBJ->alarm));
	CQU_OBJ->player = 0;
	CQU_OBJ->action = NULL;
	if (!(ft_enqueue(commandqueue.pool, cmd, 0)))
			return (EXIT_FAILURE);		//error.memory
	printf("Nodes available in commandqueue pool : %d\n", (commandqueue.pool)->qlen);
	return (EXIT_SUCCESS);
}

static t_dblist	*popfrompool(void)
{
	printf("Nodes available in commandqueue pool : %d\n", (commandqueue.pool)->qlen);
	return (ft_popfirst(commandqueue.pool));
}
