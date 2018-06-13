/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandset_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:14:04 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 22:15:32 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int32_t		advance(void *entity);
static int32_t		ft_fork(void *entity);

__attribute__((constructor))void	construct_playercommands_set1(void)
{
	eventlookup[0] = {"advance", &advance, 7};
	eventlookup[1] = {"fork", &ft_fork, 42};
}

static int32_t	ft_fork(void *entity)
{
	t_player *pl;

	pl = (t_player *)entity;
	if (egg.incubate(pl) == -1)
		communicate.toclient.outgoing(pl->c_fd, "ko\n");
	else
		communicate.toclient.outgoing(pl->c_fd, "ok\n");
	return (EXIT_SUCCESS);
}

static int32_t	advance(__attribute__((unused))void *entity)
{
	printf("player advanced\n");
	return (EXIT_SUCCESS);
}
