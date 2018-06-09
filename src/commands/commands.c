/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 16:44:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "commands.h"

static int32_t	advance(int32_t cl);

t_command_methods commands = {
	&death
};

t_commhold		commandlookup = {
	{"advance", &advance, 7}
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
	int32_t		ncommands;

	ncommands = 12;
	pl = SRV_ALLP->lookup[cl];
	while (i < ncommands)
	{
		if (ft_strequ(pl->buf, commandlookup[i]->str))
		{
			commands.add(&(commandlookup[i]), cl);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	commands.fail(cl);
	return (EXIT_SUCCESS);
}

static int32_t	add(t_command *comm, int32_t cl)
{
	t_dblist	*temp;
	t_command	set;

	temp = commandqueue.popfrompool();
	set = (t_command *)(temp->data);
	set->action = comm->action;
	server.setalarm(set->alarm, comm->factor);
	set->player = cl;
	commandqueue.addtoqueue(set);
}

static void		fail(int32_t cl)
{
	communicate.to_client.outgoing(cl, "ko\n");
}

static int32_t	advance(__attribute__((unused))int32_t cl)
{
	printf("player advanced\n");
	return (EXIT_SUCCESS);
}
