/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 18:36:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# define RAND_RESOURCE ((((((SRV_BORD.tiles)[x]).column)[y]).resources).items)

typedef struct			s_board_methods
{
	int32_t				(*new)(void);
	int32_t				(*send_dimensions)(int32_t);
	void				(*resource_gen)(void);
}						t_board_methods;

extern t_board_methods	board;

#endif
