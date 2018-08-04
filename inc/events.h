/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:58:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/21 12:10:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define NCOMMANDS 12
# define EAT 13
# define EGGCOMMAND 14
# define LVLUP 15
# define REC_GEN 16

typedef struct		s_event	t_event;

typedef struct				s_sacrifice_required
{
	int8_t					players;
	int8_t					resources[7];
}							t_sacrifice_required;

typedef struct		s_eventhold
{
	char			*str;
	int32_t			(*action)(void *);
	float			factor;
}					t_eventhold;

typedef struct		s_event
{
	t_dblist  		container;
	t_timeval 		alarm;
	int32_t	  		(*action)(void *);
	void	  		*entity;
	char			message[513];
	t_eventhold		*eventhold;
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
	void			(*removeall)(void *, int32_t);
	void			(*fail)(int32_t);
	void			(*iswaiting)(t_player *);
}					t_event_methods;

t_event_methods				event;
t_eventhold					eventlookup[17];
extern t_sacrifice_required		sacrifice[9];

#endif
