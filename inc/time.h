/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:44:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 10:29:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef struct			s_time_methods
{
	int32_t				(*comparetime)(t_timeval *);
	void				(*cleartime)(t_timeval *);
	void				(*settimer)(t_timeval **);
	void				(*setalarm)(t_timeval *, float);
}						t_time_methods;

extern t_server_methods	time;

#endif
