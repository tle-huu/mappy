/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:19:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 16:52:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static void		food(uint64_t *items);
static void		line(uint64_t *items);
static void		sibu(uint64_t *items);
static void		dera(uint64_t *items);

__attribute__((constructor))void		construct_invminusone(void)
{
	inventory.minus.food = &food;
	inventory.minus.line = &line;
	inventory.minus.sibu = &sibu;
	inventory.minus.dera = &dera;
}

static void		food(uint64_t *items)
{
	uint64_t	item;

	item = FOOD(*items);
	if (item > 0)
	{
		item--;
		*items = FOOD_INS(*items, item);
	}
}

static void		line(uint64_t *items)
{
	uint64_t	item;

	item = LINEMATE(*items);
	if (item > 0)
	{
		item--;
		*items = LINEMATE_INS(*items, item);
	}
}

static void		sibu(uint64_t *items)
{
	uint64_t	item;

	item = SIBUR(*items);
	if (item > 0)
	{
		item--;
		*items = SIBUR_INS(*items, item);
	}
}

static void		dera(uint64_t *items)
{
	uint64_t	item;

	item = DERAUMERE(*items);
	if (item > 0)
	{
		item--;
		*items = DERAUMERE_INS(*items, item);
	}
}
