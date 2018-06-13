/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:58:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 22:15:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define NCOMMANDS 2
# define EATCOMMAND 1
# define EGGCOMMAND 2

"command string, action to do, timing factor for setting alarm"
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
	t_dblist  		*container;
}					t_event;

typedef struct		s_eventqueue
{
	t_queue			*data;
	int32_t			(*new)(void);
	int32_t			(*sort)(t_dblist *, t_dblist *);
	int32_t			(*add)(t_command *);
	t_dblist		*(*pop)(void);
	int32_t			(*check)(void);
}					t_eventqueue;

typedef struct		s_eventpool
{
	t_queue			*data;
	int32_t			(*new)(void);
	int32_t			(*add)(void);
	t_dblist		*(*pop)(void);
}					t_eventpool;

typedef struct		s_event_methods
{
	t_eventpool		pool;
	t_eventqueue	queue;
	int32_t			(*lookup)(int32_t);
	int32_t			(*add)(t_commhold *, int32_t);
	void			(*fail)(int32_t);
}					t_event_methods;

t_event_methods		event;
t_eventhold			eventlookup[4];

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
