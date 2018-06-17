/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:37:04 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 16:43:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static void		add(uint64_t *items, int32_t iresource);
static void		ft_remove(uint64_t *items, int32_t iresource);

__attribute__((constructor))void		construct_inventory(void)
{
	inventory.add = &add;
	inventory.remove = &ft_remove;
}

static void		add(uint64_t *items, int32_t iresource)
{
	if (iresource == 0)
		inventory.plus.food(items);
	else if (iresource == 1)
		inventory.plus.line(items);
	else if (iresource == 2)
		inventory.plus.sibu(items);
	else if (iresource == 3)
		inventory.plus.dera(items);
	else if (iresource == 4)
		inventory.plus.mend(items);
	else if (iresource == 5)
		inventory.plus.phir(items);
	else if (iresource == 6)
		inventory.plus.thys(items);
}

static void		ft_remove(uint64_t *items, int32_t iresource)
{
	if (iresource == 0)
		inventory.minus.food(items);
	else if (iresource == 1)
		inventory.minus.line(items);
	else if (iresource == 2)
		inventory.minus.sibu(items);
	else if (iresource == 3)
		inventory.minus.dera(items);
	else if (iresource == 4)
		inventory.minus.mend(items);
	else if (iresource == 5)
		inventory.minus.phir(items);
	else if (iresource == 6)
		inventory.minus.thys(items);
}
