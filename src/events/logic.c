/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:31:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 22:30:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "time.h"
#include "communication.h"

# define PLAYER_ENT ((t_player *)entity)

static int32_t		lookup(int32_t cl);
static int32_t		add(t_eventhold *eventhold, void *entity, int32_t preprocess);
static void			fail(int32_t cl);

__attribute__((constructor))void	construct_eventlogic(void)
{
	event.lookup = &lookup;
	event.add = &add;
	event.fail = &fail;
}

static int32_t	lookup(int32_t cl)
{
	t_player	*pl;
	int32_t		i;

	pl = SRV_ALLP.lookup[cl];
	i = 0;
	printf("Looking up event |%s|\n", RECVBUF);
	while (i < NCOMMANDS)
	{
		if (ft_strequ(RECVBUF, eventlookup[i].str))
		{
			printf("event found\n");
			event.add(&(eventlookup[i]), pl, 1);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	event.fail(cl);
	return (EXIT_SUCCESS);
}

static int32_t	add(t_eventhold *eventhold, void *entity, int32_t preprocess)
{
	t_dblist	*temp;
	t_event		*ev;

	temp = event.pool.pop();
	ev = (t_event *)(temp->data);
	ev->action = eventhold->action;
	time.setalarm(&(ev->alarm), eventhold->factor);
	ev->entity = entity;
	ev->container = temp;
	if (preprocess)
	{
		if (SRV_ALLP.status[PLAYER_ENT->c_fd] == WORKING)
		{
			if (PLAYER_ENT->pending.qlen < 9)
				ft_enqueue(&(PLAYER_ENT->pending), ev->container, 0);
			else
				event.queue.add(ev);
		}
	}
	event.queue.add(ev);
	return (EXIT_SUCCESS);
}

static void		fail(int32_t cl)
{
	communication.outgoing(cl, "ko\n");
}
