/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 10:45:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/14 10:41:06 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "board.h"
#include "inventory.h"
#include "communication.h"

/* method function prototypes */
static int32_t	send_dimensions(int32_t cl);
static int32_t	new(void);
static void		resource_gen(void);
static void		setplayer(t_player *pl);

__attribute__((constructor))void	construct_board(void)
{
	board.new = &new;
	board.send_dimensions = &send_dimensions;
	board.resource_gen = &resource_gen;
	board.setplayer = &setplayer;
}

static int32_t	new(void)
{
	int32_t	x;

	printf("Creating the board\n");
	x = 0;
	if (!(SRV_BORD.tiles =
				(t_tile *)(calloc(1, sizeof(t_tile) * SRV_BORD.x))))
		return (EXIT_FAILURE);
	while (x < SRV_BORD.x)
	{
		if (!(((SRV_BORD.tiles)[x]).column =
					(t_tile *)(calloc(1, sizeof(t_tile) * SRV_BORD.y))))
			return (EXIT_FAILURE);
		x++;
	}
	board.resource_gen();
	return (EXIT_SUCCESS);
}

static int32_t	send_dimensions(int32_t cl)
{
	char	*num;
	char	*str;
	int32_t	nlen;

	nlen = ft_numlen(SRV_BORD.x);
	nlen += ft_numlen(SRV_BORD.y);
	nlen += 2;
	if (!(num = ft_itoa(SRV_BORD.x))
		|| !(str = (char *)calloc(1, (nlen + 1)))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(str = strcat(str, " "))
		|| !(num = ft_itoa(SRV_BORD.y))
		|| !(str = ft_strfreecat(str, num))
		|| !(str = strcat(str, "\n"))
		|| (communication.outgoing(cl, str) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	free(str);
	return (EXIT_SUCCESS);
}

static inline __attribute__((always_inline))void	rand_resc(uint32_t x,
		uint32_t y)
{
	uint32_t	resc;

	resc = arc4random_uniform((uint32_t)7);
	if (resc == 0)
		RAND_RESOURCE = inventory.ad_food(RAND_RESOURCE);
	else if (resc == 1)
		RAND_RESOURCE = inventory.ad_line(RAND_RESOURCE);
	else if (resc == 2)
		RAND_RESOURCE = inventory.ad_sibu(RAND_RESOURCE);
	else if (resc == 3)
		RAND_RESOURCE = inventory.ad_dera(RAND_RESOURCE);
	else if (resc == 4)
		RAND_RESOURCE = inventory.ad_mend(RAND_RESOURCE);
	else if (resc == 5)
		RAND_RESOURCE = inventory.ad_phir(RAND_RESOURCE);
	else if (resc == 6)
		RAND_RESOURCE = inventory.ad_thys(RAND_RESOURCE);
}

static void		resource_gen(void)
{
	int32_t		ntiles;
	uint32_t	gen;
	uint32_t	x;
	uint32_t	y;

	printf("Populating with resources\n");
	x = 0;
	y = 0;
	ntiles = ((SRV_BORD.x * SRV_BORD.y) >> 4);
	while (ntiles-- > 0)
	{
		gen = arc4random_uniform((uint32_t)11);
		x = arc4random_uniform((uint32_t)SRV_BORD.x);
		y = arc4random_uniform((uint32_t)SRV_BORD.y);
		while (gen-- > 0)
			rand_resc(x, y);
	}
}

static void		setplayer(t_player *pl)
{
	int32_t		x;
	int32_t		y;

	x = pl->location.x;
	y = pl->location.y;
	(((((SRV_BORD.tiles)[x]).column)[y]).players)[pl->c_fd] = pl;
}
