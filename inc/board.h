/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 11:45:39 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

typedef struct			s_board_methods
{
	int32_t				(*new)(void);
	int32_t				(*send_dimens)(int32_t);
}						t_board_methods;

extern t_board_methods	board;

#endif
