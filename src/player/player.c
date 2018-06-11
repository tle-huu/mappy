/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/10 17:07:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "board.h"
#include "client.h"
#include "communication.h"
#include "commands.h"
#include "inventory.h"
#include "player.h"
#include "team.h"

#define PBUF ((SRV_ALLP.lookup)[cl])->buf

/* method function prototypes */
static int32_t	add_toteam(int32_t cl);
static int32_t	new(int32_t cl);
static int32_t	parse_command(int32_t cl);
static void		placeonboard(int32_t cl);
static int32_t	createpool(void);
static void		death(void);
static void		addtopool(t_player *add);

/* method object */
t_player_methods	player = {
	NULL,
	&new,
	&createpool,
	&add_toteam,
	&parse_command,
	&placeonboard,
	&createpool,
	&death,
	&addtopool
};

static int32_t	new(int32_t cl)
{
	t_player	*pl;
	int32_t		ret;
	int32_t		i;
	
	printf("Creating new player <%d>\n", cl);
	ret  = 0;
	i = 0;
	if (!(pl = player.frompool()))
		return (EXIT_FAILURE);
	pl->c_fd = cl;
	(SRV_ALLP.lookup)[cl] = pl;
	while (i++ < 10)
		inventory.ad_food(pl->inventory.items);
	player.timeofdeath(pl);
	return (EXIT_SUCCESS);
}

static t_player		*frompool(void)
{
	t_dblist	*temp;
	t_player	*pl;

	temp = ft_popfirst(player.pool);
	pl = (t_player *)(temp->data);
	return (pl);
}

static int32_t	createpool(void)
{
	t_player	*temp;
	int32_t		i;
	int32_t		reps;

	i = 0;
	reps = MAX_CLIENTS;
	if (!(player.pool = (t_queue *)calloc(1, sizeof(t_queue))))
		return (EXIT_FAILURE); // memory error
	while (i < reps)
	{
		if (!(temp = (t_player *)calloc(1, sizeof(t_player)))
			|| !(temp->expiration = (t_expiration *)calloc(1, sizeof(t_expiration)))
			|| !(ft_enqueue(player.pool, temp, sizeof(t_player))))
			return (EXIT_FAILURE); // memory error
		i++;
	}
	return (EXIT_SUCCESS);
}

static int32_t	add_toteam(int32_t cl)
{
	t_player	*pl;
	int32_t		ret;
	int32_t		i;

	pl = (SRV_ALLP.lookup)[cl];
	ret = 0;
	i = 0;
	// add client removal on too many attempts
	if ((ret = communicate.fromclient.incoming(pl)) == -1)
		return (EXIT_SUCCESS);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((i = team.name_exists(cl)) == -1)
	{
		ret = communicate.toclient.outgoing(cl, "INVALID TEAMNAME\n");
		pl->conn_attempts++;
		if (pl->conn_attempts == 10)
			client.del(cl);
	}
	else
	{
		ret = team.add_player(cl, i);
		SRV_ALLP.client_stat[cl] = ACCEPTED;
	}
	return (ret);
}

static int32_t	parse_command(int32_t cl)
{
	char	*firstword_delim;
	char	hold;

	if (communicate.fromclient.incoming((SRV_ALLP.lookup)[cl]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((firstword_delim = strchr(PBUF, ' ')))
	{
		hold = *firstword_delim;
		*firstword_delim = '\0';
	}
	commands.lookup(cl);
	return (EXIT_SUCCESS);
}

static void		placeonboard(int32_t cl)
{
	t_player	*pl;

	pl = (SRV_ALLP.lookup)[cl];
	pl->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl->location.orientation = arc4random_uniform((uint32_t)4);
	board.setplayer(cl);
}

static void		death(void)
{
	char			*str;
	t_expiration	*expiration;
	t_dblist		*temp;
	t_player		*riplayer;

	temp = ft_popfirst(deathqueue.players);
	riplayer = (t_player *)((t_expiration *)temp->data)->entity;
	// generate death message to send client
	expiration = riplayer->expiration;
	if (!FOOD(riplayer->inventory.items))
	{
		bzero(riplayer, sizeof(t_player));
		riplayer->expiration = expiration;
		communicate.toclient.outgoing(riplayer->c_fd, "death\n");
		player.addtopool(riplayer);
	}
}

static void		addtopool(t_player *add)
{
	ft_enqueue(player.pool, add, 0);
	printf("Player added back to player pool\n");
}

static void		timeofdeath(t_player *pl)
{
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
