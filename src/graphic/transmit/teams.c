/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teams.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 21:02:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 21:05:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"

static int32_t		all(t_graphic *gr);

__attribute__((constructor))void		construct_transmit_teams(void)
{
	graphic.transmit.teams.all = &all;
}

static int32_t		all(t_graphic *gr)
{
	int32_t	i;

	i = 0;
	while (i < SRV_GENV.nteams)
	{
		ft_memset((void *)SENDBUF, 0, 100);
		SENDBUF = strcat(SENDBUF, "tna ");
		SENDBUF = strcat(SENDBUF, SRV_TEAM[i].name);
		SENDBUF = strcat(SENDBUF, "\n");
		communication.outgoing(gr->c_fd, SENDBUF);
		i++;
	}
	return (EXIT_SUCCESS);
}
