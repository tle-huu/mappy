/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/31 18:29:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <termios.h>
# include "client.h"
# include "libft.h"

# define SRV_SOCK g_servenv->sock
# define SRV_GENV g_servenv->gamenv

t_servenv				*g_servenv;

typedef	struct			s_board
{
	int32_t				x;
	int32_t				y;
}						t_board;

typedef struct			s_inventory
{
	int32_t				rock;
}						t_inventory;

typedef struct			s_player
{
	int32_t				level;
	t_inventory			inventory;
}						t_player;

typedef struct			s_team
{
	char				*name;
	t_player			**players;
}						t_team;

typedef struct			s_gamenv
{
	int32_t				nteams;
	int32_t				maxclients;
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

typedef struct			s_servenv
{
	int32_t				curr_client;
	t_socks				sock;
	t_board				board;
	t_gamenv			gamenv;
	t_team				*teams;
}						t_servenv;

typedef struct			s_action
{
	char 				*buf;
	char				*comm;
	int64_t				comm_len;
	char				*param;
	int64_t				param_len;
	char				*message;
	int64_t				message_len;
}						t_action;

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
