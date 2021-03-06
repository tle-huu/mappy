/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 22:59:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <math.h>
# include <netdb.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/time.h>
# include "libft.h"
# include "board.h"
# include "vehicle.h"

# define PEEK 42
# define NOT_ACCEPTED 1
# define JOINVEHICLE 2
# define JOINGRAPHIC 3
# define VEHICLE 10
# define GRAPHIC 11
# define SIMULATE 75
# define LOADMAP 8
# define XYMAP 69
# define CLEPIPE 66
# define UNKNOWNMAP 53
# define GAMEOVER 242
# define WELCOME "WELCOME\n"

typedef void 			(*sig_t) (int);
typedef struct			timeval		t_timeval;

void					construct_servergetopts(void);
void					construct_server(void);
sig_t					signal(int sig, sig_t func);

typedef struct			s_server_getopts
{
	int8_t				boardType;
	int32_t				(*destinations_nb)(char **, t_opts *);
	int32_t				(*starts_nb)(char **, t_opts *);
	int32_t				(*boardload)(char **, t_opts *);
	int32_t				(*boardx)(char **, t_opts *);
	int32_t				(*boardy)(char **, t_opts *);
	int32_t				(*port)(char **, t_opts *);
	int32_t				(*maxclients)(char **, t_opts *);
}						t_server_getopts;

typedef struct			s_simenv
{
	int32_t				maxinitial_clients;
	int32_t				connected_vehicles;
	uint64_t			track_vehicleid;
	void				*entitytoremove;
	float				timeinterval;
}						t_simenv;

typedef struct			s_client_assoc
{
	int8_t				status[FD_SETSIZE];
	void				*lookup[FD_SETSIZE];
}						t_client_assoc;

typedef struct			s_server
{
	t_server_getopts	opts;
	t_client_assoc		clients;
	t_simenv			simenv;
	t_timeval			time;
	t_timeval			starting_time;
	char				*sendbuf;
	int32_t				nsend;
	uint8_t				flag;
	char				recvbuf[513];
	int32_t				(*io)(void);
	void				(*usagewarning)(char *);
	int32_t				(*new)(void);
}						t_server;

t_server				server;
t_opts					arr_opts[8];

#endif
