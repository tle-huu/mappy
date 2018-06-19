/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:10:51 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 20:22:12 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
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

	ft_memset((void *)SENDBUF, 0, 100);
	num = ft_itoa(SRV_BORD.x + 1);
	SENDBUF = strcat(SENDBUF, "msz ");
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(SRV_BORD.y + 1);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.outgoing(gr->c_fd, SENDBUF);
	return (EXIT_SUCCESS);
}

static int32_t		timeunit(t_graphic *gr)
{
	char	*num;
	int32_t	interval;

	interval = (int32_t)SRV_GENV.timeinterval;
	ft_memset((void *)SENDBUF, 0, 100);
	num = ft_itoa(interval);
	SENDBUF = strcat(SENDBUF, "sgt ");
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, "\n");
	communication.outgoing(gr->c_fd, SENDBUF);
	return (EXIT_SUCCESS);
}
