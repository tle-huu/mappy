/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 14:30:30 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# include "vehicle.h"

# define PLAYERLIST (((((board.data.tiles)[x]).column)[y]).vehicleslist)

typedef struct			s_tile
{
	t_vehicle			*vehicles[FD_SETSIZE];
	t_queue				vehicleslist;
	struct s_tile		*column;
}						t_tile;

typedef	struct			s_board_data
{
	int32_t				x;
	int32_t				y;
	t_tile				*tiles;
}						t_board_data;

typedef struct			s_board
{
	t_board_data		data;
	int32_t				(*new)(void);
	int32_t				(*send_dimensions)(int32_t);
	void				(*setvehicle)(t_vehicle *);
	void				(*removevehicle)(t_vehicle *pl);
}						t_board;

t_board					board;

#endif
