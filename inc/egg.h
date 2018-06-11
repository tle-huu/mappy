/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:27:39 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 15:44:09 by nkouris          ###   ########.fr       */
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
	t_expiration	*expiration;
}					t_egg;

typedef struct		s_egg_methods
{
	t_queue			*pool;
	int32_t			(*createpool)(void);
	void			(*death)(void);
	void			(*addtopool)(t_egg *add);
}					t_egg_methods;

extern t_egg_methods	eggs;

#endif
