/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:29:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 20:33:12 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "board.h"

static int32_t		see(void *object);

__attribute__((constructor))void		construct_playercommands_broadcast(void)
{
}

static int32_t		broadcast(void *object)
{
	t_player	*pl;

	pl = (t_player *)((t_event *)object)->entity;
}
