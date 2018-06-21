/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incantation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 12:41:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/21 13:20:19 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "graphics.h"
#include "communication.h"

static void	start(t_player *pl);
static void	result(t_player *pl);

__attribute__((constructor)) void construct_transmit_incantation(void)
{
	graphic.transmit.incantation.start = &start;
	graphic.transmit.incantation.result = &result;
}

static void			_plid(t_player *pl)
{
	char	*num;

	num = ft_itoa(pl->player_id);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
}

static void			_level(t_player *pl)
{
	char	*num;

	num = ft_itoa(pl->level);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
}

static void			_tileloc(t_player *pl)
{
	char	*num;

	num = ft_itoa(pl->location.x);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
	num = ft_itoa(pl->location.y);
	SENDBUF = ft_strfreecat(SENDBUF, num);
	SENDBUF = strcat(SENDBUF, " ");
}

static void	_fillog(t_player *pl)
{
	SENDBUF = strcat(SENDBUF, "pic ");
	_tileloc(pl);
	_level(pl);
	_plid(pl);
}

static void _fillpl(t_player *pl)
{
	_plid(pl);
}

static void	_endspace(void)
{
	int32_t	strip;

	strip = strlen(SENDBUF);
	SENDBUF[strip - 1] = '\0';
	SENDBUF = strcat(SENDBUF, "\n");
}

static void	result(t_player *pl)
{
	SENDBUF = strcat(SENDBUF, "plv ");
	_plid(pl);
	_level(pl);
	_endspace();
	communication.graphical(NULL, SENDBUF);
}

static void	start(t_player *pl)
{
	if (!SENDBUF[0])
		_fillog(pl);
	else if (pl)
		_fillpl(pl);
	else
	{
		_endspace();
		communication.graphical(NULL, SENDBUF);
		bzero(SENDBUF, g_servenv->nsend);
	}
}
