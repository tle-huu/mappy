/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 21:51:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "commands.h"
#include "commandqueue.h"
#include "communication.h"

# define PLAYER_ENT ((t_player *)entity)

static int32_t	lookup(int32_t cl);
static int32_t	isvalid(t_commhold *comm, void *entity);
static int32_t	advance(void *entity);
static int32_t	eat(void *entity);
static void		fail(int32_t cl);

t_command_methods commands = {
	&lookup,
	&isvalid,
	&fail
};

t_commhold		commandlookup[] = {
	{"advance", &advance, 7},
	{"fork", &ft_fork, 42}
	{NULL, &eat, 126},
	{NULL, &egg.hatch, 600}
	/*
	{"right", &commands.right, 7},
	{"left", &commands.left, 7},
	{"see", &commands.see, 7},
	{"inventory", &commands.inventory, 1},
	{"take", &commands.take, 7},
	{"put", &commands.put, 7},
	{"kick", &commands.kick, 7},
	{"broadcast", &commands.broadcast, 7},
	{"incantation", &commands.incantation, 300},
	{"fork", &commands.fork, 42},
	{"connect_nbr", &commands.connect_nbr, 0},
	*/
};

static int32_t	lookup(int32_t cl)
{
	t_player	*pl;
	int32_t		i;

	pl = SRV_ALLP.lookup[cl];
	i = 0;
	printf("Looking up command |%s|\n", pl->buf);
	while (i < NCOMMANDS)
	{
		if (ft_strequ(pl->buf, commandlookup[i].str))
		{
			printf("Command found\n");
			commands.isvalid(&(commandlookup[i]), pl, 1);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	commands.fail(cl);
	return (EXIT_SUCCESS);
}

static int32_t	isvalid(t_commhold *commhold, void *entity, int32_t preprocess)
{
	t_dblist	*temp;
	t_command	*command;

	temp = commandqueue.popfrompool();
	command = (t_command *)(temp->data);
	command->action = commhold->action;
	server.commandalarm(&(command->alarm), commhold->factor);
	command->entity = entity;
	command->container = temp;
	if (preprocess)
	{
		if (SRV_ALLP.client_status[PLAYER_ENT->c_fd] == WORKING)
		{
			if (PLAYER_ENT->pending.qlen < 9)
				ft_enqueue(PLAYER_ENT->pending, command->container, 0);
			else
			{
				communicate.toclient.outgoing(PLAYER_ENT->c_fd, "ko\n");
				commandqueue.addtopool(command);
			}
		}
	}
	commandqueue.addtoqueue(command);
	return (EXIT_SUCCESS);
}

static void		fail(int32_t cl)
{
	communicate.toclient.outgoing(cl, "ko\n");
}

static int32_t	eat(void *entity)
{
	t_player	*pl;

	pl = (t_player *)entity;
	inventory.rm_food(pl->inventory.items);
	if (!(FOOD(pl->inventory.items)))
		player.impendingdeath(pl);
	else
		player.eating(pl);
	return (EXIT_SUCCESS);
}

static int32_t	ft_fork(void *entity)
{
	t_player *pl;

	pl = (t_player *)entity;
	// send ok to player .. put egg.hatch on command queue
	if (egg.incubate(pl) == -1)
		communicate.toclient.outgoing(pl->c_fd, "ko\n");
	else
		communicate.toclient.outgoing(pl->c_fd, "ok\n");
	return (EXIT_SUCCESS);
}

static int32_t	advance(__attribute__((unused))void *entity)
{
	printf("player advanced\n");
	return (EXIT_SUCCESS);
}
