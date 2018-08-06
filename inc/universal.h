/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:46:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 14:34:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIVERSAL_H
# define UNIVERSAL_H

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>

# define MAX_CLIENTS (FD_SETSIZE - 10)

typedef struct				s_socket
{
	int32_t					sockfd;
	int32_t					opt_val;
	int32_t					nfds;
	int32_t					port;
	socklen_t				socklen;
	struct sockaddr_in		address;
	struct sockaddr_in		temp;
	struct protoent			*proto;
	fd_set					*input;
	fd_set					*copy;
	int32_t					(*init_select)(void);
	int32_t					(*set)(void);
}							t_socket;

t_servenv					*g_servenv;

# endif
