/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathqueue.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:06:39 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 17:07:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEATH_H
# define DEATH_H

/*
**	The expiration struct is a generalized data structure that holds
**	entity info as a pointer, and the time that the entity should die.
**	
**	The corresponding entity (player or egg) will have reference to this
**	and is allowed to modify the timesup values, triggering a queue pop
**	and then pqueue re-addition to the corresponding deathtrack.
**	
**	Deathtrack checks will be instigated in the main body of select,
**	right before the timer is set for the next loop.
*/

typedef struct	s_expiration
{
	t_timeval	alarm;
	void		*entity;
}				t_expiration;

typedef	struct	s_deathqueue
{
	t_queue		*players;
	t_queue		*eggs;
	int32_t		(*check)(void);
	int32_t		(*player)(void);
	int32_t		(*egg)(void);
}				t_deathqueue;

extern t_deathqueue	deathqueue;

#endif
