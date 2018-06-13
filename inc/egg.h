/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:27:39 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 16:07:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EGG_H
# define EGG_H

/*
**	Every will have its own queue of eggs, pulled from here, on the eggs.pool
**	queue of pre-allocated objects.  This will avoid heavy use of system
**	calls to create and destory these objects at runtime. 
*/

typedef struct		s_egg
{
	int32_t			teamindex;
	uint64_t		egg_id;
	t_location		location;
	t_expiration	expiration;
	t_dblist		*container;
	t_dblist		*deathcontainer;
}					t_egg;

typedef struct		s_eggpool
{
	t_queue			*data;
	int32_t			(*new)(void);
	void			(*add)(t_egg *);
	t_dblist		*(*pop)(void);
}					t_eggpool;

typedef struct		s_eggplace
{
	int32_t			(*onboard)(t_egg *);
}					t_eggplace;

typedef struct		s_eggdeath
{
	void			soon(t_egg *egg);
	void			now(void);
}					t_eggdeath;

typedef struct		s_egg_methods
{
	t_eggpool		pool;
	t_eggplace		place;
	t_eggdeath		death;
	int32_t			(*incubate)(t_player *);
	int32_t			(*hatch)(t_egg *);
}					t_egg_methods;

t_egg_methods		egg;

#endif
