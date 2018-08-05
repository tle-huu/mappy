/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:07:15 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:42:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct	s_graphic_vehicles
{
	int32_t		(*all)(t_graphic *);
	int32_t		(*position)(t_vehicle *);
	int32_t		(*connected)(t_vehicle *);
	int32_t		(*death)(t_vehicle *);
}				t_graphic_vehicles;

typedef struct	s_graphic_teams
{
	int32_t		(*all)(t_graphic *);
}				t_graphic_teams;

typedef struct	s_graphic_tiles
{
	int32_t		(*all)(t_graphic *);
	int32_t		(*one)(t_graphic *, int, int);
}				t_graphic_tiles;

typedef struct			s_graphic_transmit
{
	t_graphic_tiles		tiles;
	t_graphic_vehicles	vehicles;
	int32_t				(*mapsize)(t_graphic *);
	int32_t				(*timeunit)(t_graphic *);
}						t_graphic_transmit;

typedef struct	s_graphic_methods
{
	t_graphic_transmit	transmit;
	int32_t				(*new)(int32_t);
	int32_t				(*greeting)(t_graphic *);
	int32_t				(*clear)(t_graphic *);
}				t_graphic_methods;

t_graphic_methods	graphic;

#endif