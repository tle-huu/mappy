/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:10:51 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "graphics.h"
#include "communication.h"

static int32_t		mapsize(t_graphic *gr);
static int32_t		timeunit(t_graphic *gr);

__attribute__((constructor))void		construct_graphic_transmit(void)
{
	graphic.transmit.mapsize = &mapsize;
	graphic.transmit.timeunit = &timeunit;
}

static int32_t		mapsize(t_graphic *gr)
{
	char	*num;

	num = ft_itoa(board.data.x + 1);
	server.sendbuf = strcat(server.sendbuf, "msz ");
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(board.data.y + 1);
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.outgoing(gr->c_fd, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}

static int32_t		timeunit(t_graphic *gr)
{
	char	*num;
	int32_t	interval;

	interval = (int32_t)server.simenv.timeinterval;
	num = ft_itoa(interval);
	server.sendbuf = strcat(server.sendbuf, "sgt ");
	server.sendbuf = ft_strfreecat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	communication.outgoing(gr->c_fd, server.sendbuf);
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}
