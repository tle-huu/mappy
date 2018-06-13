/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:46:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 16:44:25 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIVERSAL_H
# define UNIVERSAL_H

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <math.h>
# include <netdb.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/time.h>
# include "libft.h"
# include "inventory.h"
# include "player.h"
# include "board.h"
# include "client.h"
# include "communication.h"
# include "death.h"
# include "egg.h"
# include "events.h"
# include "graphics.h"
# include "server.h"
# include "team.h"
# include "time.h"

typedef struct		s_player
{
	int32_t			c_fd;
	uint64_t		player_id;
	int8_t			conn_attempts;
	int8_t			level;
	char			buf[513];
	t_inventory		inventory;
	t_location		location;
	t_expiration	expiration;
	t_queue			pending;
	t_team			*team;
	t_dblist		*container;
}					t_player;

typedef	struct			s_location
{
	int32_t				x;
	int32_t				y;
	int8_t				orientation;
}						t_location;

# endif
