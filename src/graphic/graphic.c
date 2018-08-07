/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:07:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 16:06:42 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "graphics.h"
#include "transmit.h"

static int32_t		new(int32_t cl);
static int32_t		greeting(t_graphic *gr);
static int32_t		clear(t_graphic *gr);

__attribute__((constructor))void		construct_graphic(void)
{
	graphic.new = &new;
	graphic.greeting = &greeting;
	graphic.clear = &clear;
}

static int32_t		new(int32_t cl)
{
	t_graphic	*gr;

	printf("  Graphic fd : %d\n", cl);
	if (!(gr = (t_graphic *)calloc(1, sizeof(t_graphic))))
		return (EXIT_FAILURE);
	gr->c_fd = cl;
	server.clients.lookup[cl] = gr;
	server.clients.status[cl] = GRAPHIC;
	gr->container.data = gr;
	ft_enqueue(&(graphic.data), &(gr->container), 0);
	graphic.greeting(gr);
	return (EXIT_SUCCESS);
}

static int32_t		clear(t_graphic *gr)
{
	ft_middel(&(graphic.data), &(gr->container));
	free(gr);
	return (EXIT_SUCCESS);
}

static int32_t		greeting(t_graphic *gr)
{
	transmit.flag = GRAPHICAL;
	if ((transmit.tiles.mapsize(gr) == EXIT_FAILURE)
		|| (transmit.timeunit(gr) == EXIT_FAILURE)
		|| (transmit.tiles.all(gr) == EXIT_FAILURE)
		|| (transmit.vehicles.all(gr) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
