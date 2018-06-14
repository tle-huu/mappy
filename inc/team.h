/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:41:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 23:04:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEAM_H
# define TEAM_H


typedef struct	s_team_methods
{
	int32_t		(*name_exists)(int32_t);
	int32_t		(*add_player)(t_player *, int32_t);
	int32_t		(*send_freespots)(int32_t, t_team *);
}				t_team_methods;

t_team_methods	team;

#endif
