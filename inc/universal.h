/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:46:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/19 17:36:42 by nkouris          ###   ########.fr       */
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

# define SRV_ALLP g_servenv->allplayers
# define SRV_SOCK g_servenv->socket
# define SRV_GENV g_servenv->gamenv
# define SRV_BORD g_servenv->board
# define SRV_CMND g_servenv->command
# define SRV_TIME g_servenv->time
# define SRV_RIPT g_servenv->deathtime
# define SRV_TEAM g_servenv->teams
# define SENDBUF g_servenv->sendbuf
# define RECVBUF g_servenv->recvbuf
# define PEEK 42
# define NOT_ACCEPTED 1
# define JOINTEAM 2
# define JOINGRAPHIC 3
# define ACCEPTED 10
# define GRAPHIC 11
# define WORKING 100
# define RESTING 101
# define DOOMED 33
# define DEAD 66
# define MAX_CLIENTS (FD_SETSIZE - 10)

# define NORTH 1
# define EAST 2
# define SOUTH 4
# define WEST 8

# define WELCOME "WELCOME\n"

typedef struct	timeval		t_timeval;
typedef struct	s_team		t_team;

typedef struct			s_graphic
{
	int32_t				c_fd;
	t_dblist			container;
}						t_graphic;

typedef struct			s_inventory
{
	uint64_t			items;
}						t_inventory;

typedef	struct			s_location
{
	int32_t				x;
	int32_t				y;
	int8_t				orientation;
}						t_location;

typedef struct		s_egg
{
	int32_t			teamindex;
	uint64_t		egg_id;
	uint64_t		progenitor;
	t_location		location;
	t_timeval		alarm;
	t_dblist		*container;
	t_dblist		*deathcontainer;
}					t_egg;

typedef struct		s_player
{
	int32_t			c_fd;
	uint64_t		player_id;
	int32_t			teamindex;
	int8_t			conn_attempts;
	int8_t			level;
	t_inventory		inventory;
	t_location		location;
	t_timeval		alarm;
	t_queue			pending;
	t_dblist		tilecontainer;
	char			message[513];
	t_team			*team;
	t_dblist		*container;
}					t_player;

typedef struct			s_tile
{
	t_inventory			resources;
	t_player			*players[FD_SETSIZE];
	t_queue				playerslist;
	struct s_tile		*column;
}						t_tile;

typedef	struct			s_board
{
	int32_t				x;
	int32_t				y;
	t_tile				*tiles;
}						t_board;

typedef struct  s_team
{
	char		*name;
	int32_t		nplayers;
	int32_t		teamindex;
	t_player	*players[FD_SETSIZE];
	t_queue 	eggqueue;
}				t_team;

typedef struct			s_gamenv
{
	int32_t				nteams;
	int32_t				maxinitial_clients;
	int32_t				maxingame_players;
	uint64_t			track_playerid;
	uint64_t			track_eggid;
	void				*entitytoremove;
	float				timeinterval;
}						t_gamenv;

typedef struct			s_socket
{
	int32_t				sockfd;
	int32_t				opt_val;
	int32_t				nfds;
	int32_t				port;
	socklen_t			socklen;
	struct sockaddr_in	address;
	struct sockaddr_in	temp;
	struct protoent		*proto;
	fd_set				*input;
	fd_set				*copy;
}						t_socket;

typedef struct			s_allplayers
{
	int8_t				status[FD_SETSIZE];
	void				*lookup[FD_SETSIZE];
}						t_allplayers;

typedef struct			s_servenv
{
	t_allplayers		allplayers;
	t_socket			socket;
	t_board				board;
	t_gamenv			gamenv;
	t_timeval			time;
	t_timeval			deathtime;
	t_queue				graphical;
	t_timeval			*keeptimer;
	t_team				*teams;
	char				*sendbuf;
	int32_t				nsend;
	char				recvbuf[513];
}						t_servenv;

t_servenv				*g_servenv;

# endif
