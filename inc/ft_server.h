/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:41:35 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 19:13:26 by nkouris          ###   ########.fr       */
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

# define KEY "PASS NICK JOIN MSG PRVMSG "
# define SERVER_CONFIG ".ftirc_config"
# define SRV_SOCK (server->socks)
# define SRV_CLIENT (server->clients[server->curr_client])
# define MAX_ATTEMPTS -3

t_servenv				*g_servenv;

typedef struct			s_socks
{
	int32_t				sockfd;
	int32_t				opt_val;
	int32_t				nfds;
	socklen_t			socklen;
	struct sockaddr_in	address;
	struct sockaddr_in	temp;
	struct protoent		*proto;
	fd_set				*input;
	fd_set				*copy;
}						t_socks;

typedef	struct			s_channel
{
	char				*name;
	t_client			**clients;
}						t_channel;

typedef struct			s_servenv
{
	t_socks				socks;
	char				*name;
	char				*setpath;
	int32_t				pathfd;
	t_client			**clients;
	t_dblist			*channels;
	int32_t				curr_client;
	int32_t				port;
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
**	cli_gets
*/

int32_t		get_port(char **argv, t_opts *opt);

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
