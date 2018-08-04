/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:23:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 20:24:12 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static int32_t		mend(uint64_t *items);
static int32_t		phir(uint64_t *items);
static int32_t		thys(uint64_t *items);

__attribute__((constructor))void		construct_invminustwo(void)
{
	inventory.minus.mend = &mend;
	inventory.minus.phir = &phir;
	inventory.minus.thys = &thys;
}

static int32_t		mend(uint64_t *items)
{
	uint64_t	item;

	item = MENDIANE(*items);
	if (item > 0)
	{
		item--;
		*items = MENDIANE_INS(*items, item);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int32_t		phir(uint64_t *items)
{
	uint64_t	item;

	item = PHIRAS(*items);
	if (item > 0)
	{
		item--;
		*items = PHIRAS_INS(*items, item);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int32_t		thys(uint64_t *items)
{
	uint64_t	item;

	item = THYSTAME(*items);
	if (item > 0)
	{
		item--;
		*items = THYSTAME_INS(*items, item);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
