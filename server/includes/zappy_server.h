/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy_server.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:30:53 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/02 04:17:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_SERVER_H
# define ZAPPY_SERVER_H

#include "zappy.h"


typedef struct s_team t_team;

typedef struct	s_server
{
	t_player		**players;
	t_map			*map;
	t_team			**teams;
	t_pqueue		*events;
	fd_set			server_fds;
	int				max;
	struct timeval	time;
	// float		time;
	int				min_players;
	int				players_nb;
}				t_server;

#endif
