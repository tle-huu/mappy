/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:11:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 16:21:44 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMM_H
# define FT_COMM_H

typedef struct			s_srv_toclient
{
	int32_t				(*welcome)();
}						t_srv_toclient;

typedef struct			s_communicate
{
	t_srv_toclient		toclient;
}						t_communicate;

t_communicate			communicate;
extern t_srv_toclient	toclient;

#endif
