/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandqueue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:12:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/08 17:27:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "commandqueue.h"

#define CQU_OBJ ((t_command *)(cmd))

static int32_t	check(void);
static int32_t	addtoqueue(t_dblist *command);
static int32_t	createpool(void);
static int32_t	addtopool(void);
static t_dblist	*popfrompool(void);

t_commandqueue_methods commandqueue = {
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
	if (SRV_CMND.commandqueue)
	{
		cmd = (SRV_CMND.commandqueue->first);
		while (cmd)
		{
			cmd = (SRV_CMND.commandqueue->first);
			if (server.comparetime(&CQU_OBJ->alarm))
			{
				CQU_OBJ->action();
				commandqueue.addtopool();
			}
			else
				break ;
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
	if (!(ft_penqueue(SRV_CMND.commandqueue, command, 0, &timeoutsort)))
		return (EXIT_FAILURE); //?? error.memory() ??
	return (EXIT_SUCCESS);
}

static int32_t	createpool(void)
{
	t_command	*temp;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = (SRV_GENV.nteams * 6 * 10);
	if (!(SRV_CMND.opencommand = (t_queue *)calloc(1, sizeof(t_queue)))
		|| !(SRV_CMND.commandqueue = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE);		//error.memory
	while (i < reps)
	{
		if (!(temp = (t_command *)calloc(1, sizeof(t_command)))
			|| !(ft_enqueue(SRV_CMND.opencommand, temp, sizeof(t_command))))
			return (EXIT_FAILURE);		//error.memory
		i++;
	}
	return (EXIT_SUCCESS);
}

static int32_t	addtopool(void)
{
	t_dblist	*cmd;

	cmd = ft_popfirst(SRV_CMND.commandqueue);
	server.cleartime(&(CQU_OBJ->alarm));
	CQU_OBJ->player = 0;
	CQU_OBJ->action = NULL;
	if (!(ft_enqueue(SRV_CMND.opencommand, cmd, 0)))
			return (EXIT_FAILURE);		//error.memory
	return (EXIT_SUCCESS);
}

static t_dblist	*popfrompool(void)
{
	return (ft_popfirst(SRV_CMND.opencommand));
}
