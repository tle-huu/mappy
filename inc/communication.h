/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:11:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 11:45:43 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMM_H
# define FT_COMM_H

typedef struct			s_srv_toclient
{
	int32_t				(*outgoing)(int32_t, char *);
}						t_srv_toclient;

typedef struct			s_client_tosrv
{
	int32_t				(*incoming)(t_player *);
}						t_client_tosrv;

typedef struct			s_communicate
{
	t_srv_toclient		toclient;
	t_client_tosrv		fromclient;
}						t_communicate;

extern t_communicate	communicate;
extern t_srv_toclient	toclient;
extern t_client_tosrv	fromclient;

#endif
