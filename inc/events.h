/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:58:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 12:19:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define NCOMMANDS 4
# define EAT 13
# define EGGCOMMAND 14

typedef struct		s_eventhold
{
	char			*str;
	int32_t			(*action)(void *);
	float			factor;
}					t_eventhold;

typedef struct		s_event
{
	t_timeval 		alarm;
	int32_t	  		(*action)(void *);
	void	  		*entity;
	t_eventhold		*eventhold;
	t_dblist  		*container;
}					t_event;

typedef struct		s_eventqueue
{
	t_queue			*data;
	int32_t			(*new)(void);
	int32_t			(*sort)(t_dblist *, t_dblist *);
	int32_t			(*add)(t_event *);
	t_dblist		*(*pop)(void);
	int32_t			(*check)(void);
}					t_eventqueue;

typedef struct		s_eventpool
{
	t_queue			*data;
	int32_t			(*new)(void);
	void			(*add)(t_event *);
	t_dblist		*(*pop)(void);
}					t_eventpool;

typedef struct		s_event_methods
{
	t_eventpool		pool;
	t_eventqueue	queue;
	int32_t			(*lookup)(int32_t);
	int32_t			(*add)(t_eventhold *, void *, int32_t);
	void			(*remove)(void *);
	void			(*fail)(int32_t);
	void			(*is_waiting)(t_player *);
}					t_event_methods;

t_event_methods		event;
t_eventhold			eventlookup[15];

/* FOR REFERENCE
 *
**	t_eventhold		eventlookup[] = {
**		{"right", &commands.right, 7},
**		{"left", &commands.left, 7},
**		{"see", &commands.see, 7},
**		{"inventory", &commands.inventory, 1},
**		{"take", &commands.take, 7},
**		{"put", &commands.put, 7},
**		{"kick", &commands.kick, 7},
**		{"broadcast", &commands.broadcast, 7},
**		{"incantation", &commands.incantation, 300},
**		{"fork", &commands.fork, 42},
**		{"connect_nbr", &commands.connect_nbr, 0},
**	};
*/


#endif
