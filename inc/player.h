/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:30:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 22:21:46 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct			s_player
{
	int32_t				c_fd;
	uint64_t			player_id;
	int8_t				conn_attempts;
	int8_t				level;
	char				buf[513];
	t_inventory			inventory;
	t_location			location;
	t_expiration		expiration;
	t_queue				pending;
	t_team				*team;
	t_dblist			*container;
}						t_player;

typedef struct	s_player_methods
{
	t_queue		*pool;
	int32_t		(*new)(int32_t);
	int32_t		(*createpool)(int32_t);
	int32_t		(*add_toteam)(int32_t);
	int32_t		(*parse_command)(int32_t);
	void		(*placeonboard)(int32_t);
	int32_t		(*createpool)(void);
	void		(*death)(void);
	void		(*addtopool)(t_player *add);
}				t_player_methods;

extern t_player_methods	player;

#endif
