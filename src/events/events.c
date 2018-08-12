/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:48:06 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 19:25:22 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"
#include "events.h"
#include "time.h"
#include "communication.h"
#include "transmit.h"

# define PLAYER_ENT ((t_vehicle *)entity)

static int32_t		lookup(int32_t cl);
static int32_t		add(t_eventhold *eventhold, void *entity);
static void			ft_remove(void *entity);
static void			iswaiting(t_vehicle *pl);

void		__attribute__((constructor))construct_eventlogic(void)
{
	event.lookup = &lookup;
	event.add = &add;
	event.removeall = &ft_remove;
	event.iswaiting = &iswaiting;
}

static void		_vehicle_thoroughput(void)
{
	int32_t	x;
	int32_t	y;
	char	*temp;

	x = 0;
	y = 0;
	temp = strchr(server.recvbuf, ' ');
	for (int32_t i = 0; i < 2; i++)
	{
		temp = strchr((temp + 1), ' ');
	}
	x = atoi(temp);
	temp = strchr((temp + 1), ' ');
	y = atoi(temp);
	(board.data.tiles[x]).column[y].vehicle_thoroughput++;
}

static void		_data_mine(void)
{
	_vehicle_thoroughput();
}

static int32_t	lookup(int32_t cl)
{
	t_vehicle	*pl;
	char		*temp;
	int32_t		i;

	pl = (t_vehicle *)server.clients.lookup[cl];
	i = 0;
	if ((temp = ft_strchr(server.recvbuf, ' ')))
		*temp = '\0';
	if (ft_strequ(server.recvbuf, eventlookup[0].str))
	{
		*temp = ' ';
		event.add(&(eventlookup[0]), pl);
		i++;
	}
	else
		client.crash(cl);
	printf("exited lookup\n");
	return (EXIT_SUCCESS);
}

static int32_t	add(t_eventhold *eventhold, void *entity)
{
	double		factor;
	char		*shift;
	char		*endshift;
	t_dblist	*temp;
	t_event		*ev;

	temp = event.pool.pop();
	ev = (t_event *)(temp->data);
	ev->action = eventhold->action;
	ev->eventhold = eventhold;
	_data_mine();
	shift = strrchr(server.recvbuf, ' ');
	endshift = shift + strlen(shift);
	factor = strtod(shift, &endshift);
	time.setalarm(&(ev->alarm), factor);
	ev->entity = entity;
	transmit.vehicles.datagram_pass(entity);
	event.queue.add(ev);
	bzero(server.recvbuf, 513);
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
		event.add(ev->eventhold, pl);
		event.pool.add(ev);
	}
}
