/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 19:07:34 by nkouris          ###   ########.fr       */
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
# define PLAYER 10
# define GRAPHIC 11
# define WORKING 100
# define INCANTING 101
# define INCANTED 102
# define LEVELING 103
# define DOOMED 33
# define DEAD 66
# define SIMULATE 75

# define NORTH 0x1
# define EAST 0x2
# define SOUTH 0x4
# define WEST 0x8

# define WELCOME "WELCOME\n"

typedef struct			timeval		t_timeval;

void					construct_servergetopts(void);
void					construct_server(void);

typedef struct			s_server_getopts
{
	int32_t				(*boardx)(char **, t_opts *);
	int32_t				(*boardy)(char **, t_opts *);
	int32_t				(*timeinterval)(char **, t_opts *);
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
	char				*sendbuf;
	int32_t				nsend;
	uint8_t				flag;
	char				recvbuf[513];
	int32_t				(*io)(void);
	void				(*usagewarning)(char *);
	int32_t				(*new)(void);
}						t_server;

t_server				server;
t_opts					arr_opts[6];

#endif
