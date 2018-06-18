/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:07:15 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/18 02:18:39 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct	s_graphic_eggs
{
	int32_t		(*all)(t_graphic *);
}				t_graphic_eggs;

typedef struct	s_graphic_players
{
	int32_t		(*all)(t_graphic *);
	int32_t		(*items)(t_player *);
}				t_graphic_players;

typedef struct	s_graphic_teams
{
	int32_t		(*all)(t_graphic *);
}				t_graphic_teams;

typedef struct	s_graphic_tiles
{
	int32_t		(*all)(t_graphic *);
}				t_graphic_tiles;

typedef struct			s_graphic_transmit
{
	t_graphic_tiles		tiles;
	t_graphic_teams		teams;
	t_graphic_players	players;
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
