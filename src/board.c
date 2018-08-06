/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 10:45:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/05 19:19:18 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "board.h"
#include "events.h"
#include "communication.h"

/* method function prototypes */
static int32_t	send_dimensions(int32_t cl);
static int32_t	new(void);
static void		setvehicle(t_vehicle *pl);
static void		removevehicle(t_vehicle *pl);

__attribute__((constructor))void	construct_board(void)
{
	board.new = &new;
	board.send_dimensions = &send_dimensions;
	board.setvehicle = &setvehicle;
	board.removevehicle = &removevehicle;
}

static int32_t	new(void)
{
	int32_t	x;

	printf("Creating the board\n");
	x = 0;
	if (!(board.data.tiles =
				(t_tile *)(calloc(1, sizeof(t_tile) * (board.data.x + 1)))))
		return (EXIT_FAILURE);
	while (x < board.data.x + 1)
	{
		if (!(((board.data.tiles)[x]).column =
					(t_tile *)(calloc(1, sizeof(t_tile) * (board.data.y + 1)))))
			return (EXIT_FAILURE);
		x++;
	}
	return (EXIT_SUCCESS);
}

static int32_t	send_dimensions(int32_t cl)
{
	char	*num;
	char	*str;
	int32_t	nlen;

	nlen = ft_numlen(board.data.x + 1);
	nlen += ft_numlen(board.data.y + 1);
	nlen += 2;
	if (!(num = ft_itoa(board.data.x + 1))
		|| !(str = (char *)calloc(1, (nlen + 1)))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(str = strcat(str, " "))
		|| !(num = ft_itoa(board.data.y + 1))
		|| !(str = ft_strfreecat(str, num))
		|| !(str = strcat(str, "\n"))
		|| (communication.outgoing(cl, str) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	free(str);
	return (EXIT_SUCCESS);
}

static void		setvehicle(t_vehicle *pl)
{
	int32_t		x;
	int32_t		y;

	x = pl->location.x;
	y = pl->location.y;
	(((((board.data.tiles)[x]).column)[y]).vehicles)[pl->c_fd] = pl;
	ft_enqueue(&(PLAYERLIST), &(pl->tilecontainer), 0);
}

static void		removevehicle(t_vehicle *pl)
{
	int32_t		x;
	int32_t		y;

	x = pl->location.x;
	y = pl->location.y;
	(((((board.data.tiles)[x]).column)[y]).vehicles)[pl->c_fd] = NULL;
	ft_middel(&(PLAYERLIST), &(pl->tilecontainer));
}
