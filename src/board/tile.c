/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:30:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 11:10:31 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "board.h"
#include "inventory.h"

static int32_t	check(int32_t x, int32_t y, int32_t iresource);

t_resources resources[] = {
	{"food"},
	{"linemate"},
	{"sibur"},
	{"deraumere"},
	{"mendiane"},
	{"phiras"},
	{"thystame"},
};

__attribute__((constructor))void		construct_boardtile(void)
{
	board.tile.check = &check;
}

static int32_t	check(int32_t x, int32_t y, int32_t iresource)
{
	if (iresource == 0)
		return (FOOD(RESOURCE));
	else if (iresource == 1)
		return (LINEMATE(RESOURCE));
	else if (iresource == 2)
		return (SIBUR(RESOURCE));
	else if (iresource == 3)
		return (DERAUMERE(RESOURCE));
	else if (iresource == 4)
		return (MENDIANE(RESOURCE));
	else if (iresource == 5)
		return (PHIRAS(RESOURCE));
	else if (iresource == 6)
		return (THYSTAME(RESOURCE));
	return (0);
}
