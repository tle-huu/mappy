/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:11:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 20:06:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMM_H
# define FT_COMM_H

#include "graphics.h"

typedef struct			s_communication
{
	int32_t				(*outgoing)(int32_t, char *);
	int32_t				(*incoming)(int32_t);
	int32_t				(*printraw)(void);
	int32_t				(*graphical)(t_graphic *, char *);
	int32_t				(*vehicles)(t_vehicle *, void *, int8_t);
	int32_t				(*newclient)(int32_t);
}						t_communication;

t_communication			communication;

#endif
