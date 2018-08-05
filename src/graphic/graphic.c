/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:07:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:52:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "graphics.h"

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
	SRV_CLNT.lookup[cl] = gr;
	SRV_CLNT.status[cl] = GRAPHIC;
	gr->container.data = gr;
	ft_enqueue(&(g_servenv->graphical), &(gr->container), 0);
	graphic.greeting(gr);
	return (EXIT_SUCCESS);
}

static int32_t		clear(t_graphic *gr)
{
	ft_middel(&(g_servenv->graphical), &(gr->container));
	free(gr);
	return (EXIT_SUCCESS);
}

static int32_t		greeting(t_graphic *gr)
{
	if ((graphic.transmit.mapsize(gr) == EXIT_FAILURE)
		|| (graphic.transmit.timeunit(gr) == EXIT_FAILURE)
		|| (graphic.transmit.tiles.all(gr) == EXIT_FAILURE)
		|| (graphic.transmit.vehicles.all(gr) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
