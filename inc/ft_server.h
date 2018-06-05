/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/04 19:05:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <termios.h>
# include "libft.h"

# define SRV_SOCK g_servenv->sock
# define SRV_GENV g_servenv->gamenv
# define SRV_BORD g_servenv->board
# define SRV_TEMP g_servenv->tempcomm
# define SRV_CLNT g_servenv->curr_client
# define PEEK 42
# define NOT_ACCEPTED 21
# define ACCEPTED 42

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define WELCOME "WELCOME\n"

typedef struct			s_team		t_team;
typedef struct			s_servenv	t_servenv;

t_servenv				*g_servenv;

typedef	struct			s_location
{
	int32_t				x;
	int32_t				y;
	int8_t				orientation;
}						t_location;

typedef struct			s_inventory
{
	int32_t				linemate;
	int32_t				sibur;
	int32_t				deraumere;
	int32_t				mendiane;
	int32_t				phiras;
	int32_t				thystame;
//	t_inventorymethods	*vtbl;
}						t_inventory;

typedef struct			s_player
{
	int32_t				level;
	int32_t				c_fd;
	int8_t				conn_attempts;
	char				buf[513];
	t_inventory			inventory;
	t_location			location;
	t_team				*team;
//	t_playermethods		*vtbl;
}						t_player;

typedef struct			s_tile
{
	t_inventory			resources;
	t_player			**players;
}						t_tile;

typedef	struct			s_board
{
	int32_t				x;
	int32_t				y;
	t_tile				**tiles;
//	t_boardmethods		*vtbl;
}						t_board;

typedef struct			s_team
{
	char				*name;
	int32_t				n;
	t_player			*players[FD_SETSIZE];
//	t_teammethods		*vtbl;
}						t_team;

typedef struct			s_gamenv
{
	int32_t				nteams;
	int32_t				maxclients;
	int32_t				nclients;
	int32_t				timeint;
}						t_gamenv;

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

typedef struct			s_tempcomm
{
	int8_t				purgatory[FD_SETSIZE];
	t_player			*lost[FD_SETSIZE];
}						t_tempcomm;

typedef struct			s_servenv
{
	int32_t				curr_client;
	t_tempcomm			tempcomm;
	t_socks				sock;
	t_board				board;
	t_gamenv			gamenv;
	t_team				*teams;
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
int32_t		pregame_io(void);


//void			init_fd_select(int32_t fd, t_servenv *server);
//int32_t			ublock_dispatch(t_servenv *server);
//int32_t			ft_passconfirm(t_servenv *server, t_action *act);
//int32_t			param_split(char *buf, t_action *act);
//int32_t			comm_split(char *buf, t_action *act);
//int32_t			server_config(t_servenv *server, char **envp);
//int32_t			server_client_comm(t_client *client, t_servenv *server);
//int32_t			ft_addnick(t_servenv *server, t_action *act);
//int32_t			default_nick(t_client *client, char **envp);
//int32_t			combine_send(int (*f)(t_client *client), t_client *client);
//int32_t			send_pass(t_client *client);
//int32_t			send_ognick(t_client *client);
//void			user_addtochannel(t_servenv *server, t_channel *channel);
//int32_t			check_dupchannel(t_servenv *server, t_action *act);
//int32_t			new_channel(t_servenv *server, t_action *act);
//int32_t			ft_joinchannel(t_servenv *server, t_action *act);
//int32_t			ft_message(t_servenv *server, t_action *act);
//int32_t			ft_chanmessage(t_servenv *server, t_action *act);
//int32_t			ft_usnmessage(t_servenv *server, t_action *act);
//void			message_split(char *buf, t_action *act);
//int32_t			usn_split(char *buf, t_action *act);

#endif
