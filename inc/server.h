/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 00:44:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include "universal.h"

void					construct_servergetopts(void);

typedef struct			s_server_getopts
{
	int32_t				(*boardx)(char **, t_opts *);
	int32_t				(*boardy)(char **, t_opts *);
	int32_t				(*timeinterval)(char **, t_opts *);
	int32_t				(*port)(char **, t_opts *);
	int32_t				(*maxclients)(char **, t_opts *);
}						t_server_getopts;

typedef struct			s_server
{
	t_server_getopts	opts;
	int32_t				(*io)(void);
	void				(*usagewarning)(char *);
}						t_server;

t_server				server;
t_opts					arr_opts[6];

#endif
