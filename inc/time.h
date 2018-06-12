/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:44:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 15:10:46 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef struct			s_team
{
	char				*name;
	int32_t				nplayers;
	int32_t				teamindex;
	t_player			*players[FD_SETSIZE];
	t_queue				*eggqueue;
}						t_team;

typedef struct			s_server_methods
{
	int32_t				(*comparetime)(t_timeval *);
	void				(*cleartime)(t_timeval *);
	void				(*settimer)(t_timeval **);
	void				(*setalarm)(t_timeval *, float);
}						t_server_methods;

extern t_server_methods	server;

#endif
