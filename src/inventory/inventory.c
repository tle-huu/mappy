/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:37:04 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 22:35:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "board.h"
#include "inventory.h"

/* method function prototypes */
uint64_t	ad_food(uint64_t inv);
uint64_t	rm_food(uint64_t inv);
uint64_t	ad_line(uint64_t inv);
uint64_t	rm_line(uint64_t inv);
uint64_t	ad_sibu(uint64_t inv);
uint64_t	rm_sibu(uint64_t inv);
uint64_t	ad_dera(uint64_t inv);
uint64_t	rm_dera(uint64_t inv);
uint64_t	ad_mend(uint64_t inv);
uint64_t	rm_mend(uint64_t inv);
uint64_t	ad_phir(uint64_t inv);
uint64_t	rm_phir(uint64_t inv);
uint64_t	ad_thys(uint64_t inv);
uint64_t	rm_thys(uint64_t inv);

/* method objects */
t_inventory_methods	inventory = {
	&ad_food,
	&rm_food,
	&ad_line,
	&rm_line,
	&ad_sibu,
	&rm_sibu,
	&ad_dera,
	&rm_dera,
	&ad_mend,
	&rm_mend,
	&ad_phir,
	&rm_phir,
	&ad_thys,
	&rm_thys
};

uint64_t	ad_food(uint64_t inv)
{
	uint64_t	item;

	item = FOOD(inv);
	if (item <= 255)
	{
		item++;
		inv = FOOD_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_food(uint64_t inv)
{
	uint64_t	item;

	item = FOOD(inv);
	if (item > 0)
	{
		item--;
		inv = FOOD_INS(inv, item);
	}
	return (inv);
}

uint64_t	ad_line(uint64_t inv)
{
	uint64_t	item;

	item = LINEMATE(inv);
	if (item <= 255)
	{
		item++;
		inv = LINEMATE_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_line(uint64_t inv)
{
	uint64_t	item;

	item = LINEMATE(inv);
	if (item > 0)
	{
		item--;
		inv = LINEMATE_INS(inv, item);
	}
	return (inv);
}

uint64_t	ad_sibu(uint64_t inv)
{
	uint64_t	item;

	item = SIBUR(inv);
	if (item <= 255)
	{
		item++;
		inv = SIBUR_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_sibu(uint64_t inv)
{
	uint64_t	item;

	item = SIBUR(inv);
	if (item > 0)
	{
		item--;
		inv = SIBUR_INS(inv, item);
	}
	return (inv);
}

uint64_t	ad_dera(uint64_t inv)
{
	uint64_t	item;

	item = DERAUMERE(inv);
	if (item <= 255)
	{
		item++;
		inv = DERAUMERE_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_dera(uint64_t inv)
{
	uint64_t	item;

	item = DERAUMERE(inv);
	if (item > 0)
	{
		item--;
		inv = DERAUMERE_INS(inv, item);
	}
	return (inv);
}

uint64_t	ad_mend(uint64_t inv)
{
	uint64_t	item;

	item = MENDIANE(inv);
	if (item <= 255)
	{
		item++;
		inv = MENDIANE_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_mend(uint64_t inv)
{
	uint64_t	item;

	item = MENDIANE(inv);
	if (item > 0)
	{
		item--;
		inv = MENDIANE_INS(inv, item);
	}
	return (inv);
}

uint64_t	ad_phir(uint64_t inv)
{
	uint64_t	item;

	item = PHIRAS(inv);
	if (item <= 255)
	{
		item++;
		inv = PHIRAS_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_phir(uint64_t inv)
{
	uint64_t	item;

	item = PHIRAS(inv);
	if (item > 0)
	{
		item--;
		inv = PHIRAS_INS(inv, item);
	}
	return (inv);
}
uint64_t	ad_thys(uint64_t inv)
{
	uint64_t	item;

	item = THYSTAME(inv);
	if (item <= 255)
	{
		item++;
		inv = THYSTAME_INS(inv, item);
	}
	return (inv);
}

uint64_t	rm_thys(uint64_t inv)
{
	uint64_t	item;

	item = THYSTAME(inv);
	if (item > 0)
	{
		item--;
		inv = THYSTAME_INS(inv, item);
	}
	return (inv);
}
