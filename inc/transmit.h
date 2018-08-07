/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:51:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 22:33:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSMIT_H
# define TRANSMIT_H

# define GRAPHICAL 1
# define VEHICLE 2

typedef struct			s_transmit_vehicles
{
	int32_t				(*all)(void *);
	int32_t				(*position)(t_vehicle *);
	int32_t				(*connected)(t_vehicle *);
	int32_t				(*exited)(t_vehicle *);
	int32_t				(*goal)(void *);
	int32_t				(*endtransmit)(void *);
	int32_t				(*datagram_pass)(t_vehicle *);
}						t_transmit_vehicles;

typedef struct			s_transmit_tiles
{
	int32_t				(*mapsize)(void *);
	int32_t				(*all)(void *);
}						t_transmit_tiles;

typedef struct			s_transmit
{
	uint8_t				flag;
	t_transmit_vehicles	vehicles;
	t_transmit_tiles	tiles;
	int32_t				(*timeunit)(t_graphic *);
}						t_transmit;

t_transmit				transmit;

#endif
