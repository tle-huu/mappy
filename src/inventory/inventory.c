/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:37:04 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 16:03:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static int32_t		add(uint64_t *items, int32_t iresource);
static int32_t		ft_remove(uint64_t *items, int32_t iresource);
static int32_t		check(uint64_t items, int32_t iresource);

__attribute__((constructor))void		construct_inventory(void)
{
	inventory.add = &add;
	inventory.remove = &ft_remove;
	inventory.check = &check;
}

static int32_t		add(uint64_t *items, int32_t iresource)
{
	if (iresource == 0)
		return (inventory.plus.food(items));
	else if (iresource == 1)
		return (inventory.plus.line(items));
	else if (iresource == 2)
		return (inventory.plus.sibu(items));
	else if (iresource == 3)
		return (inventory.plus.dera(items));
	else if (iresource == 4)
		return (inventory.plus.mend(items));
	else if (iresource == 5)
		return (inventory.plus.phir(items));
	else if (iresource == 6)
		return (inventory.plus.thys(items));
	return (EXIT_FAILURE);
}

static int32_t		ft_remove(uint64_t *items, int32_t iresource)
{
	if (iresource == 0)
		return (inventory.minus.food(items));
	else if (iresource == 1)
		return (inventory.minus.line(items));
	else if (iresource == 2)
		return (inventory.minus.sibu(items));
	else if (iresource == 3)
		return (inventory.minus.dera(items));
	else if (iresource == 4)
		return (inventory.minus.mend(items));
	else if (iresource == 5)
		return (inventory.minus.phir(items));
	else if (iresource == 6)
		return (inventory.minus.thys(items));
	return (EXIT_FAILURE);
}

static int32_t		check(uint64_t items, int32_t iresource)
{
	if (iresource == 0)
		return (FOOD(items));
	else if (iresource == 1)
		return (LINEMATE(items));
	else if (iresource == 2)
		return (SIBUR(items));
	else if (iresource == 3)
		return (DERAUMERE(items));
	else if (iresource == 4)
		return (MENDIANE(items));
	else if (iresource == 5)
		return (PHIRAS(items));
	else if (iresource == 6)
		return (THYSTAME(items));
	return (EXIT_FAILURE);
}
