/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 17:07:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <sys/select.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <math.h>
# include <netdb.h>
# include <termios.h>
# include <stdlib.h>
# include "libft.h"

# define SRV_SOCK g_servenv->sock
# define SRV_GENV g_servenv->gamenv
# define SRV_BORD g_servenv->board
# define SRV_ALLP g_servenv->allplayers
# define SRV_CLNT g_servenv->curr_client
# define SRV_CMND g_servenv->command
# define SRV_TIME g_servenv->time
# define SRV_RIP g_servenv->rip
# define PEEK 42
# define NOT_ACCEPTED 21
# define ACCEPTED 42
# define MAX_CLIENTS (FD_SETSIZE - 10)

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 4

# define WELCOME "WELCOME\n"

typedef struct			s_team		t_team;
typedef struct			s_servenv	t_servenv;
typedef struct			timeval		t_timeval;

t_servenv				*g_servenv;

typedef struct			s_server_methods
{
	int32_t				(*comparetime)(t_timeval *);
	void				(*cleartime)(t_timeval *);
	void				(*settimer)(t_timeval **);
	void				(*setalarm)(t_timeval *, float);
}						t_server_methods;

extern t_server_methods	server;


typedef	struct			s_location
{
	int32_t				x;
	int32_t				y;
	int8_t				orientation;
}						t_location;

typedef struct			s_inventory
{
	uint64_t			items;
}						t_inventory;

typedef struct			s_player
{
	int32_t				level;
	int32_t				c_fd;
	int8_t				conn_attempts;
	int8_t				orientation;
	char				buf[513];
	t_inventory			inventory;
	t_location			location;
	t_expiration		*expiration;
	t_team				*team;
	struct s_player		*next;
}						t_player;

typedef struct			s_tile
{
	t_inventory			resources;
	t_player			*players[FD_SETSIZE];
	struct s_tile		*column;
}						t_tile;

typedef	struct			s_board
{
	int32_t				x;
	int32_t				y;
	t_tile				*tiles;
}						t_board;

typedef struct			s_team
{
	char				*name;
	int32_t				nplayers;
	t_player			*players[FD_SETSIZE];
	t_queue				eggqueue;
}						t_team;

typedef struct			s_gamenv
{
	int32_t				nteams;
	int32_t				maxclients;
	int32_t				nclients;
	float				timeint;
}						t_gamenv;

typedef struct			s_command
{
	t_timeval			alarm;
	int32_t				(*action)(int32_t);
	int32_t				player;
}						t_command;

typedef struct			s_socks
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
}						t_socks;

typedef struct			s_allplayers
{
	int8_t				client_stat[FD_SETSIZE];
	t_player			*lookup[FD_SETSIZE];
}						t_allplayers;

typedef struct			s_servenv
{
	int32_t				curr_client;
	t_allplayers		allplayers;
	t_socks				sock;
	t_board				board;
	t_gamenv			gamenv;
//	t_commandpool		command;
	t_timeval			time;
	t_timeval			rip;
	t_team				*teams;
	char				*sendbuf;
}						t_servenv;

/*
**	srv_sets
*/

int32_t		srv_setboardx(char **argv, __attribute__((unused))t_opts *opt);
int32_t		srv_setboardy(char **argv, __attribute__((unused))t_opts *opt);
int32_t		srv_setport(char **argv, t_opts *opt);
int32_t		srv_setteams(char **argv, t_opts *opt);
int32_t		srv_setmaxclients(char **argv, t_opts *opt);
int32_t		srv_settimeint(char **argv, __attribute__((unused))t_opts *opt);

/*
**	cli_sets
*/


/*
**	error
*/

void		usage_warning(char *str);

/*
**	client_init
*/

int32_t		client_init(void);

/*
**	create_board
*/

int32_t		create_board(void);

/*
**	incoming
*/

//int32_t		game_io(void);
int32_t		game_io(void);

#endif
