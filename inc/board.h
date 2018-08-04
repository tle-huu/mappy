/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:28:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# define PLAYERLIST (((((SRV_BORD.tiles)[x]).column)[y]).playerslist)

typedef struct		s_board_tile
{
	int32_t			(*check)(int32_t, int32_t, int32_t);
}					t_board_tile;

typedef struct		s_board_methods
{
	t_board			data;
	t_board_tile	tile;
	int32_t			(*new)(void);
	int32_t			(*send_dimensions)(int32_t);
	void			(*setplayer)(t_player *);
	void			(*removeplayer)(t_player *pl);
}					t_board_methods;

t_board_methods		board;

#endif
