/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:30:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 15:46:13 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct	s_player_methods
{
	t_queue		*pool;
	int32_t		(*new)(int32_t);
	int32_t		(*createpool)(int32_t);
	int32_t		(*add_toteam)(int32_t);
	int32_t		(*parse_command)(int32_t);
	void		(*placeonboard)(int32_t);
	int32_t		(*createpool)(void);
	void		(*death)(void);
	void		(*addtopool)(t_player *add);
}				t_player_methods;

extern t_player_methods	player;

#endif
