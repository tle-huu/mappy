/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:30:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 19:00:25 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct	s_player_methods
{
	int32_t		(*new)(void);
	int32_t		(*add_toteam)(void);
	int32_t		(*islost)(void);
}				t_player_methods;

extern t_player_methods	player;

#endif
