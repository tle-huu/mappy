/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:23:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 16:49:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static void		mend(uint64_t *items);
static void		phir(uint64_t *items);
static void		thys(uint64_t *items);

__attribute__((constructor))void		construct_invminustwo(void)
{
	inventory.minus.mend = &mend;
	inventory.minus.phir = &phir;
	inventory.minus.thys = &thys;
}

static void		mend(uint64_t *items)
{
	uint64_t	item;

	item = MENDIANE(*items);
	if (item > 0)
	{
		item--;
		*items = MENDIANE_INS(*items, item);
	}
}

static void		phir(uint64_t *items)
{
	uint64_t	item;

	item = PHIRAS(*items);
	if (item > 0)
	{
		item--;
		*items = PHIRAS_INS(*items, item);
	}
}

static void		thys(uint64_t *items)
{
	uint64_t	item;

	item = THYSTAME(*items);
	if (item > 0)
	{
		item--;
		*items = THYSTAME_INS(*items, item);
	}
}
