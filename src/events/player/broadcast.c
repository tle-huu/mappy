/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:29:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/21 11:59:19 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "board.h"

static int32_t		broadcast(void *object);

char	*broadcasts[12] = {
	"A door opening and a plate being dropped\n",
	"Thunder and lightning\n",
	"Bells jingling on a sliegh\n",
	"Thousands of people groaning\n",
	"Salmon being slapped against rocks by bears\n",
	"A paper ball bing lit on fire\n",
	"Someone shaking a can of soda, and then opening it\n",
	"A 10000 volt fly zapper\n",
	"The sound of a ketchup bottle that is nearly empty\n",
	"Marbles rolling across a mattress topper\n",
	"Pennies being melted\n",
	"A man roasting bananas\n"
};

__attribute__((constructor))void		construct_playercommands_broadcast(void)
{
	struct s_eventhold	ev11 = {"broadcast", &broadcast, 7};

	eventlookup[11] = ev11;
}

static int32_t		_sendmessage(t_player *pl)
{
	static int32_t		destiny;
	int32_t				past;

	past = destiny;
	while (destiny == past)
		destiny = arc4random_uniform(12);
	SENDBUF = strcat(SENDBUF, "IN THE DISTANCE, YOU HEAR :\n");
	SENDBUF = strcat(SENDBUF, broadcasts[destiny]);
	communication.outgoing(pl->c_fd, SENDBUF);
	bzero(SENDBUF, g_servenv->nsend);
	return (EXIT_SUCCESS);
}

static int32_t		broadcast(void *object)
{
	int32_t		i;
	t_player	*og;
	t_player	*pl;

	og = (t_player *)((t_event *)object)->entity;
	i = 0;
	while (i < SRV_SOCK.nfds)
	{
		pl = SRV_ALLP.lookup[i];
		if (pl
			&& pl != og)
			_sendmessage(pl);
		i++;
	}
	communication.outgoing(og->c_fd, "ok\n");
	SRV_ALLP.status[og->c_fd] = PLAYER;
	event.iswaiting(og);
	return (EXIT_SUCCESS);
}
