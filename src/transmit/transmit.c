/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:10:51 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/09 21:45:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "graphics.h"
#include "transmit.h"
#include "communication.h"

static int32_t		timeunit(t_graphic *gr);

__attribute__((constructor))void		construct_graphic_transmit(void)
{
	transmit.timeunit = &timeunit;
}

static int32_t		timeunit(t_graphic *gr)
{
	char	*num;
	int32_t	interval;

	interval = (int32_t)server.simenv.timeinterval;
	num = ft_itoa(interval);
	server.sendbuf = strcat(server.sendbuf, "sgt ");
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.outgoing(gr->c_fd, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}
