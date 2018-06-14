/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandset_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:14:04 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 22:09:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "egg.h"

static int32_t		advance(void *entity);
static int32_t		ft_fork(void *entity);

__attribute__((constructor))void	construct_playercommands_set1(void)
{
	struct s_eventhold ev0 = {"advance", &advance, 7};
	struct s_eventhold ev1 = {"fork", &ft_fork, 42};
	
	eventlookup[0] = ev0;
	eventlookup[1] = ev1;
}

static int32_t	ft_fork(void *entity)
{
	t_player *pl;

	pl = (t_player *)entity;
	if (egg.incubate(pl) == -1)
		communication.outgoing(pl->c_fd, "ko\n");
	else
		communication.outgoing(pl->c_fd, "ok\n");
	return (EXIT_SUCCESS);
}

static int32_t	advance(__attribute__((unused))void *entity)
{
	printf("player advanced\n");
	return (EXIT_SUCCESS);
}
