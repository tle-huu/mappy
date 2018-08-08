/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:48:06 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 16:48:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "events.h"
#include "time.h"
#include "communication.h"
#include "transmit.h"

# define PLAYER_ENT ((t_vehicle *)entity)

static int32_t		lookup(int32_t cl);
static int32_t		add(t_eventhold *eventhold, void *entity, int32_t preprocess);
static void			ft_remove(void *entity);
static void			fail(int32_t cl);
static void			iswaiting(t_vehicle *pl);

void		__attribute__((constructor))construct_eventlogic(void)
{
	event.lookup = &lookup;
	event.add = &add;
	event.removeall = &ft_remove;
	event.fail = &fail;
	event.iswaiting = &iswaiting;
}

static int32_t	lookup(int32_t cl)
{
	t_vehicle	*pl;
	char		**split;
	char		**strings;
	char		*temp;
	int32_t		i;

	pl = (t_vehicle *)server.clients.lookup[cl];
	printf("  Looking up event |%s|\n", server.recvbuf);
	split = ft_strsplit(server.recvbuf, '\n');
	strings = split;
	while (*split)
	{
		i = 0;
		if ((temp = ft_strchr(*split, ' ')))
		{
			bzero(pl->message, 513);
			ft_strcpy(pl->message, (temp + 1));
			*temp = '\0';
		}
		while (i < NCOMMANDS)
		{
			//printf("  compare to : |%s|\n", eventlookup[i].str);
			if (ft_strequ(*split, eventlookup[i].str))
			{
				//printf("event found\n");
				event.add(&(eventlookup[i]), pl, 1);
				break ;
			}
			i++;
		}
		if (i == NCOMMANDS)
			event.fail(cl);
		free(*split);
		(split)++;
	}
	free(strings);
	printf("  [EVENT]\n  OVER\n");
	return (EXIT_SUCCESS);
}

static int32_t	pl_preprocess(void *entity, t_event *ev)
{
	//printf("  Preprocess vehicle command\n  Commands in vehicles queue : %d\n",
			//PLAYER_ENT->pending.qlen);
	//printf("  Copying this message : |%s|\n", PLAYER_ENT->message);
	if (PLAYER_ENT->message[0])
		strcpy(ev->message, PLAYER_ENT->message);
	if (server.clients.status[PLAYER_ENT->c_fd] == WORKING
		|| server.clients.status[PLAYER_ENT->c_fd] == INCANTED
		|| server.clients.status[PLAYER_ENT->c_fd] == INCANTING)
	{
		//printf("  Player is doing something already\n");
		if (PLAYER_ENT->pending.qlen < 9)
			ft_enqueue(&(PLAYER_ENT->pending), &(ev->container), 0);
		else
		{
			//printf("  Player has too many commands queued\n"); 
			event.pool.add(ev);
		}
		return (1);
	}
	return (0);
}

static int32_t	add(t_eventhold *eventhold, void *entity, int32_t preprocess)
{
	double		factor;
	char		*shift;
	char		*endshift;
	t_dblist	*temp;
	t_event		*ev;

//	printf("[EVENT]\n  Adding <%s>\n", eventhold->str);
	temp = event.pool.pop();
	ev = (t_event *)(temp->data);
	ev->action = eventhold->action;
	ev->eventhold = eventhold;
	shift = strrchr(((t_vehicle *)entity)->message, ' ');
	endshift = shift + strlen(shift);
	factor = strtod(shift, &endshift);
	time.setalarm(&(ev->alarm), factor);
	ev->entity = entity;
	if (preprocess)
	{
		if (pl_preprocess(entity, ev))
			return (EXIT_SUCCESS);
		server.clients.status[PLAYER_ENT->c_fd] = WORKING;
	}
//	printf("  Adding event to main queue\n");
	transmit.vehicles.datagram_pass(entity);
	event.queue.add(ev);
	return (EXIT_SUCCESS);
}

static void		ft_remove(void *entity)
{
	t_dblist	*temp;
	t_dblist	*temp1;

	temp = event.queue.data->first;
	while (temp)
	{
		if (((t_event *)(temp->data))->entity == entity)
		{
			//printf("\nmatching events\n");
			temp1 = temp->next;
			ft_middel(event.queue.data, temp);
			event.pool.add(temp->data);
			temp = temp1;
		}
		else
			temp = temp->next;
	}
}

static void		iswaiting(t_vehicle *pl)
{
	t_dblist	*temp;
	t_event		*ev;

	if ((temp = ft_popfirst(&(pl->pending))))
	{
		ev = (t_event *)(temp->data);
		if (ev->message[0])
			strcpy(pl->message, ev->message);
		//printf("[EVENT]\n  Pullling from vehicle's command queue\n");
		event.add(ev->eventhold, pl, 1);
		event.pool.add(ev);
	}
}

static void		fail(int32_t cl)
{
	communication.outgoing(cl, "ko\n");
}
