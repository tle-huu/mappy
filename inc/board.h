/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/10 19:48:16 by psprawka         ###   ########.fr       */
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
	uint8_t				state;
	uint32_t			vehicle_thoroughput;
}						t_tile;

typedef	struct			s_board_data
{
	int32_t				x;
	int32_t				y;
	int32_t				des;
	int32_t				starts;
	char				*filename;
	t_tile				*tiles;
	uint8_t				goal;
}						t_board_data;

typedef struct			s_board
{
	t_board_data		data;
	int32_t				(*new)(void);
	int32_t				(*load_file)(void);
	int32_t				(*send_dimensions)(int32_t);
	void				(*setvehicle)(t_vehicle *);
	void				(*removevehicle)(t_vehicle *pl);
	void 				(*dump)(void);
}						t_board;

t_board					board;

#endif
