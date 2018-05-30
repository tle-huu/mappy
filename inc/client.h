/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:41:13 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/20 19:11:17 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define MAX_CLIENTS 1024
# define CLIENT_SOCK (client->csock)

# define C_KEY "/nick /join /msg "
# define SERVER 55
# define CLIENT 100
# define NO_CMD 0

typedef struct		s_servenv t_servenv;
typedef struct		s_client t_client;
typedef struct		s_channel t_channel;
typedef struct		s_action t_action;

enum {
	PASS = 1,
	NICK,
	JOIN,
	PRVMSG
};

typedef struct			s_csock
{
	int32_t				sockfd;
	int32_t				nfds;
	socklen_t			socklen;
	struct sockaddr_in	address;
	struct protoent		*proto;
	fd_set				*input;
	fd_set				*copy;
}						t_csock;

typedef struct			s_client
{
	t_csock				csock;
	t_channel			*chanp;
	char				*nickname;
	char				*channel;
	char				*message;
	char				pass[24];
	int8_t				accepted;
	int32_t				comm;
}						t_client;

int32_t		client_init(int32_t newfd, t_servenv *server);
void		c_usn_split(char *buf, t_action *act);
int32_t		c_param_split(char *buf, t_action *act);
int32_t		c_comm_split(char *buf, t_action *act, int32_t sendr);
int32_t		digest_input(t_client *client);
int32_t		incoming_response(t_client *client);
int32_t		send_touser(t_client *client, t_action *act);
int32_t		send_tochannel(t_client *client, t_action *act);
int32_t		send_join(t_client *client, t_action *act);

#endif
