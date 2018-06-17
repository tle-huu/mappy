/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 16:19:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 16:46:02 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "inventory.h"

static void		food(uint64_t *items);
static void		line(uint64_t *items);
static void		sibu(uint64_t *items);
static void		dera(uint64_t *items);

__attribute__((constructor))void		construct_invplusone(void)
{
	inventory.plus.food	= &food;
	inventory.plus.line = &line;
	inventory.plus.sibu = &sibu;
	inventory.plus.dera = &dera;
}

static void		food(uint64_t *items)
{
	uint64_t	item;

	item = FOOD(*items);
	if (item <= 255)
	{
		item++;
		*items = FOOD_INS(*items, item);
	}
}

static void		line(uint64_t *items)
{
	uint64_t	item;

	item = LINEMATE(*items);
	if (item <= 255)
	{
		item++;
		*items = LINEMATE_INS(*items, item);
	}
}

static void		sibu(uint64_t *items)
{
	uint64_t	item;

	item = SIBUR(*items);
	if (item <= 255)
	{
		item++;
		*items = SIBUR_INS(*items, item);
	}
}

static void		dera(uint64_t *items)
{
	uint64_t	item;

	item = DERAUMERE(*items);
	if (item <= 255)
	{
		item++;
		*items = DERAUMERE_INS(*items, item);
	}
}
