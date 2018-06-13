/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/12 12:15:25 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
			|| !(ft_enqueue(player.pool, temp, sizeof(t_player))))
			return (EXIT_FAILURE); // memory error
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_dblist		*popfrompool(void)
{
	return (ft_popfirst(player.pool));
}

static void		addtopool(t_player *pl)
{
	ft_enqueue(player.pool, pl->container, 0);
	printf("Player added back to player pool\n");
}

static int32_t	new(int32_t cl)
{
	t_dblist	*temp;
	t_player	*pl;
	int32_t		ret;
	int32_t		i;
	
	printf("Creating new player <%d>\n", cl);
	ret  = 0;
	i = 0;
	if (!(temp = player.popfrompool()))
		return (EXIT_FAILURE);
	pl = (t_player *)temp->data;
	pl->container = temp;
	pl->c_fd = cl;
	pl->player_id = (SERV_GENV.track_playerid)++;
	(SRV_ALLP.lookup)[cl] = pl;
	while (i++ < 10)
		inventory.ad_food(pl->inventory.items);
	pl.expiration.entity = pl;
	player.eating(pl);
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
		ret = team.add_player(pl, i);
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

static void		impendingdeath(t_player *pl)
{
	server.setalarm(&(pl->expiration->alarm), 0);
	SRV_ALLP.status[pl->c_fd] = DOOMED;
	ft_enqueue(deathqueue.players, pl->container, 0);
}

static void		death(void)
{
	t_dblist		*temp;
	t_player		*pl;

	temp = ft_popfirst(deathqueue.players);
	pl = (t_player *)(temp->data);
	// generate death message to send client
	communicate.toclient.outgoing(pl->c_fd, "death\n");
	SRV_ALLP.client_stat[pl->c_fd] = DEAD;
	client.del(pl->c_fd);
	bzero(pl, sizeof(t_player));
	pl->container = temp;
	player.addtopool(pl);
}

static void		eating(t_player *pl)
{
	commands.isvalid(&(commandlookup[EATCOMMAND]), pl, 0);
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
