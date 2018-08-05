/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:46:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 22:02:26 by nkouris          ###   ########.fr       */
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
# include "board.h"
# include "vehicle.h"

# define SRV_CLNT g_servenv->client_data
# define SRV_SOCK g_servenv->socket
# define SRV_GENV g_servenv->gamenv
# define SRV_BORD g_servenv->board
# define SRV_CMND g_servenv->command
# define SRV_TIME g_servenv->time
# define SENDBUF g_servenv->sendbuf
# define RECVBUF g_servenv->recvbuf
# define PEEK 42
# define NOT_ACCEPTED 1
# define JOINVEHICLE 2
# define JOINGRAPHIC 3
# define PLAYER 10
# define GRAPHIC 11
# define WORKING 100
# define INCANTING 101
# define INCANTED 102
# define LEVELING 103
# define DOOMED 33
# define DEAD 66
# define MAX_CLIENTS (FD_SETSIZE - 10)

# define NORTH 1
# define EAST 2
# define SOUTH 4
# define WEST 8

# define WELCOME "WELCOME\n"

typedef struct	timeval		t_timeval;

typedef struct			s_graphic
{
	int32_t				c_fd;
	t_dblist			container;
}						t_graphic;

typedef struct			s_gamenv
{
	int32_t				maxinitial_clients;
	int32_t				connected_vehicles;
	uint64_t			track_vehicleid;
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

typedef struct			s_clients
{
	int8_t				status[FD_SETSIZE];
	void				*lookup[FD_SETSIZE];
}						t_clients;

typedef struct			s_servenv
{
	t_clients			client_data; // <-- data
	t_socket			socket; // convert to class
	t_board				board; // is class
	t_gamenv			gamenv; // <-- data
	t_timeval			time; // <-- data
	t_queue				graphical; // <-- data
	char				*sendbuf; // <-- data
	int32_t				nsend; // <-- data
	char				recvbuf[513]; // <-- data
}						t_servenv;

t_servenv				*g_servenv;

# endif
