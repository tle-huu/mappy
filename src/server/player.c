/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 19:00:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "player.h"

/* method function prototypes */
static int32_t	add_toteam(void);
static int32_t	new(void);
static int32_t	islost(void);

/* method object */
t_player_methods	player = {
	&new,
	&add_toteam,
	&islost
};

static int32_t	add_toteam(void)
{
	t_player	*p;
	int32_t		ret;
	int32_t		i;

	p = SRV_TEMP.lost[SRV_CLNT];
	i = 0;
	bzero(p->buf, 513);
	ret = 0;
	if ((ret = recv(SRV_CLNT, p->buf, 512, 0)) < 0)
		return (EXIT_FAILURE);
	if (!ret)
	{
		close(SRV_CLNT);
		FD_CLR(SRV_CLNT, SRV_SOCK.copy);
		return (EXIT_SUCCESS);
	}
	while ((i < SRV_GENV.nteams)
			&& !(ft_strequ(p->buf, g_servenv->teams[i].name)))
		i++;
	if (i == SRV_GENV.nteams)
	{
		send(SRV_CLNT, "INVALID_TEAMNAME\n", sizeof("INVALID_TEAMNAME\n"), 0);
		p->conn_attempts++;
	}
	else
	{
		p->team = &(g_servenv->teams[i]);
		(p->team->players)[SRV_CLNT] = p;
		SRV_TEMP.lost[SRV_CLNT] = NULL;
	}
	return (ret);
}

static int32_t	new(void)
{
	t_player	*p;
	int32_t		ret;
	int32_t		i;
	
	ret  = 0;
	i = 0;
	if (!(p = (t_player *)ft_memalloc(sizeof(t_player))))
		return (EXIT_FAILURE);
	p->c_fd = SRV_CLNT;
	SRV_TEMP.lost[SRV_CLNT] = p;
	return (EXIT_SUCCESS);
}

static int32_t	islost(void)
{
	if (SRV_TEMP.lost[SRV_CLNT])
		return (1);
	return (0);
}


/*
static int32_t		delete(void)
{
}

static int32_t		elevate(void)
{
}

static int32_t		see(void)
{
}

static int32_t		advance(void)
{
}

static int32_t		turn_right(void)
{
}

static int32_t		turn_left(void)
{
}

static int32_t		inventory(void)
{
}

static int32_t		take(object)
{
}

static int32_t		put(object)
{
}

static int32_t		broadcast(char *str)
{
}

static int32_t		incantation()
{
}

static int32_t		death()
{
}
*/
