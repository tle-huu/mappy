/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 16:08:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define SRV_ALLP g_servenv->allplayers
# define SRV_SOCK g_servenv->socket
# define SRV_GENV g_servenv->gamenv
# define SRV_BORD g_servenv->board
# define SRV_CMND g_servenv->command
# define SRV_TIME g_servenv->time
# define SRV_RIPT g_servenv->deathtime
# define SRV_TEAM
# define PEEK 42
# define NOT_ACCEPTED 21
# define ACCEPTED 42
# define WORKING 100
# define RESTING 50
# define DOOMED 33
# define DEAD 66
# define MAX_CLIENTS (FD_SETSIZE - 10)

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 4

# define WELCOME "WELCOME\n"

typedef struct			s_gamenv
{
	int32_t				nteams;
	int32_t				maxinitial_clients;
	int32_t				maxingame_players;
	uint64_t			track_playerid;
	uint64_t			track_eggid;
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
	t_player			*lookup[FD_SETSIZE];
}						t_allplayers;

typedef struct			s_servenv
{
	t_allplayers		allplayers;
	t_socket			socket;
	t_board				board;
	t_gamenvironment	gamenv;
	t_timeval			time;
	t_timeval			deathtime;
	t_team				*teams;
	char				sendbuf[513];
	char				recievbuf[513];
}						t_servenv;

t_servenv				*g_servenv;

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
