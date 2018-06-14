/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:44:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 17:23:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef struct	timeval	t_timeval;

typedef struct			s_time_methods
{
	int32_t				(*compare)(t_timeval *);
	void				(*settimer)(t_timeval **);
	void				(*setalarm)(t_timeval *, float);
}						t_time_methods;

t_time_methods		time;

#endif
