/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:03:50 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 15:04:39 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
# define SOCKET_H

# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>

# define MAX_CLIENTS (FD_SETSIZE - 10)

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
	int32_t				(*init_select)(void);
	int32_t				(*set)(void);
}						t_socket;

t_socket				ft_socket;

# endif
