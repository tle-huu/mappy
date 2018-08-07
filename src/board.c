/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 10:45:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 23:00:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "board.h"
#include "events.h"
#include "communication.h"

/* method function prototypes */
static int32_t	send_dimensions(int32_t cl);
static int32_t	new(void);
static int32_t	load_file(void);
static void		setvehicle(t_vehicle *pl);
static void		removevehicle(t_vehicle *pl);

__attribute__((constructor))void	construct_board(void)
{
	board.new = &new;
	board.load_file = &load_file;
	board.send_dimensions = &send_dimensions;
	board.setvehicle = &setvehicle;
	board.removevehicle = &removevehicle;
}

static void		_generate_random_board(void)
{
	int32_t	fill;
	int32_t x;
	int32_t y;

	x = 0;
	while (x <= board.data.x)
	{
		y = 0;
		while (y <= board.data.y)
		{
			fill = arc4random_uniform((uint32_t)10);
			if (fill < 2)
				(board.data.tiles[x]).column[y].state = 0;
			else
				(board.data.tiles[x]).column[y].state = 1;
			y++;
		}
		x++;
	}
}

static int32_t	new(void)
{
	int32_t	x;

	printf("Creating the board\n");
	x = 0;
	printf("Board x : %d\nBoard y : %d\n", board.data.x, board.data.y);
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
	_generate_random_board();
	return (EXIT_SUCCESS);
}

static int32_t	_fill_board(int fd, char *line)
{
	int32_t x;
	int32_t y;

	x = 0;
	while (x <= board.data.x)
	{
		y = 0;
		if (get_next_line(fd, &line) != 1)
			return (EXIT_FAILURE);
		while (y <= board.data.y)
		{
			if (!line[y])
				return (EXIT_FAILURE);
			(board.data.tiles[x]).column[y].state = line[y] - 48;
			y++;
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

static int32_t	load_file(void)
{
	int32_t	i;
	int32_t fd;
	char	*line;

	printf("Loading the board from file \"%s\"\n", board.data.filename);
	if ((fd = open(board.data.filename, O_RDONLY)) < 3
		|| get_next_line(fd, &line) != 1)
		return (EXIT_FAILURE);
	board.data.x = atoi(line) - 1;
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (EXIT_FAILURE);
	board.data.y = atoi(&(line[i])) - 1;
	board.new();
	if (_fill_board(fd, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close (fd);
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