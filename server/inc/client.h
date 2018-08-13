/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 09:51:09 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 17:41:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

typedef struct			s_client
{
	int32_t				(*new)(void);
	void				(*disconnect)(int32_t);
	void				(*crash)(int32_t);
	void				(*sigpipe)(int32_t);
}						t_client;

t_client				client;

#endif
