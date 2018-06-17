/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 21:31:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 17:44:31 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "time.h"
#include "communication.h"
#include "egg.h"

# define PLAYER_ENT ((t_player *)entity)

static int32_t		lookup(int32_t cl);
static int32_t		add(t_eventhold *eventhold, void *entity, int32_t preprocess);
static void			ft_remove(void *entity);
static void			fail(int32_t cl);
static void			is_waiting(t_player *pl);

__attribute__((constructor))void	construct_eventlogic(void)
{
	event.lookup = &lookup;
	event.add = &add;
	event.remove = &ft_remove;
	event.fail = &fail;
	event.is_waiting = &is_waiting;
}

static int32_t	lookup(int32_t cl)
{
	t_player	*pl;
	char		*temp;
	int32_t		i;

	pl = (t_player *)SRV_ALLP.lookup[cl];
	i = 0;
	printf("  Looking up event |%s|\n", RECVBUF);
	if ((temp = strchr(RECVBUF, ' ')))
	{
		bzero(pl->message, 513);
		ft_strcpy(pl->message, (temp + 1));
		*temp = '\0';
	}
	while (i < NCOMMANDS)
	{
		printf("  compare to : %s\n", eventlookup[i].str);
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

static int32_t	pl_preprocess(void *entity, t_event *ev)
{
	printf("  Preprocess player command\n  Commands in players queue : %d\n",
			PLAYER_ENT->pending.qlen);
	printf("  Copying this message : |%s|\n", PLAYER_ENT->message);
	if (PLAYER_ENT->message[0])
	{
		strcpy(ev->message, PLAYER_ENT->message);
	}
	if (SRV_ALLP.status[PLAYER_ENT->c_fd] == WORKING)
	{
		printf("  Player is working already\n");
		if (PLAYER_ENT->pending.qlen < 9)
			ft_enqueue(&(PLAYER_ENT->pending), ev->container, 0);
		else
		{
			printf("  Player has too many commands queued\n"); 
			event.pool.add(ev);
		}
		return (1);
	}
	return (0);
}

static int32_t	add(t_eventhold *eventhold, void *entity, int32_t preprocess)
{
	t_dblist	*temp;
	t_event		*ev;

	printf("[EVENT]\n  Adding <%s> to queue\n", eventhold->str);
	temp = event.pool.pop();
	ev = (t_event *)(temp->data);
	ev->action = eventhold->action;
	ev->eventhold = eventhold;
	time.setalarm(&(ev->alarm), eventhold->factor);
//	printf("[EVENT]\n  Entity to add : <%p>\n", entity);
	ev->entity = entity;
	ev->container = temp;
	if (preprocess)
	{
		if (pl_preprocess(entity, ev))
			return (EXIT_SUCCESS);
		SRV_ALLP.status[PLAYER_ENT->c_fd] = WORKING;
	}
	printf("  Adding event to main queue\n");
	event.queue.add(ev);
	return (EXIT_SUCCESS);
}

static int32_t		entity_compare(void *temp)
{
	t_event	*ev;

	ev = (t_event *)temp;
	if (ev->entity == SRV_GENV.entitytoremove)
		return (1);
	return (0);
}

static void		ft_remove(void *entity)
{
	t_dblist	*temp;

	SRV_GENV.entitytoremove = entity;
	temp = ft_dblistcritpop(event.queue.data->first, &entity_compare);
	while (temp)
	{
		if (((temp = ft_dblistcritpop(event.queue.data->first, &entity_compare))
			== event.queue.data->first))
		{
			if (event.queue.data->first == event.queue.data->last)
				event.queue.data->last = NULL;
			event.queue.data->first = NULL;
		}
		if (temp)
			event.pool.add(temp->data);
	}
}

static void		is_waiting(t_player *pl)
{
	t_dblist	*temp;

	if ((temp = ft_popfirst(&(pl->pending))))
	{
		printf("[EVENT]\n  Pullling from player's command queue\n");
		event.add(((t_event *)(temp->data))->eventhold, pl, 1);
	}
}

static void		fail(int32_t cl)
{
	communication.outgoing(cl, "ko\n");
}
