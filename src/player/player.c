/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 17:17:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "player.h"
#include "team.h"
#include "communication.h"

/* method function prototypes */
static int32_t	add_toteam(int32_t cl);
static int32_t	new(int32_t cl);
static int32_t	islost(int32_t cl);

/* method object */
t_player_methods	player = {
	&new,
	&add_toteam,
	&islost
};

static int32_t	add_toteam(int32_t cl)
{
	t_player	*p;
	int32_t		ret;
	int32_t		i;

	p = (SRV_TEMP.lost)[cl];
	ret = 0;
	i = 0;
	// add client removal on too many attempts
	if ((ret = communicate.fromclient.incoming(p)) == -1)
		return (EXIT_SUCCESS);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (team.name_exists(cl) == -1)
	{
		ret = communicate.toclient.outgoing(cl, "INVALID TEAMNAME\n");
		p->conn_attempts++;
	}
	else
	{
		ret = team.add_player(cl, i);
		SRV_TEMP.purgatory[cl] = ACCEPTED;
	}
	return (ret);
}

static int32_t	new(int32_t cl)
{
	t_player	*p;
	int32_t		ret;
	int32_t		i;
	
	printf("Creating new player <%d>\n", cl);
	ret  = 0;
	i = 0;
	if (!(p = (t_player *)ft_memalloc(sizeof(t_player))))
		return (EXIT_FAILURE);
	p->c_fd = cl;
	(SRV_TEMP.lost)[cl] = p;
	return (EXIT_SUCCESS);
}

static int32_t	islost(int32_t cl)
{
	printf("Checking if player <%d> is lost\n", cl);
	if ((SRV_TEMP.lost)[cl])
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
