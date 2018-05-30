/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_commands1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:59:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:51:05 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

int32_t		ft_joinchannel(t_servenv *server, t_action *act)
{
	t_client	*client;
	int32_t		ret;

	client = SRV_CLIENT;
	ret = 0;
	if (param_split((act->comm + 1), act) == EXIT_FAILURE
		|| (ret = check_dupchannel(server, act)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ret == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (new_channel(server, act) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int32_t		ft_passconfirm(t_servenv *server, t_action *act)
{
	char		buf[513];
	t_client	*client;

	ft_bzero(buf, 512);
	client = SRV_CLIENT;
	if (param_split(act->comm + 1, act) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	read(server->pathfd, buf, 512);
	lseek(server->pathfd, 0, SEEK_SET);
#ifdef DEBUG
	ft_printf("bufword read from file : \"%s\"\n", buf);
#endif
	if (!(ft_strequ((act->comm + 1), buf)))
	{
#ifdef DEBUG
	ft_printf("incorrect bufword : \"%s\"\n", (act->comm + 1));
#endif
		send(CLIENT_SOCK.sockfd,
				"ERR_PASSWDMISMATCH ", sizeof("ERR_PASSWDMISMATCH "), 0);
		client->accepted--;
		return (EXIT_FAILURE);
	}
	else
	{
		send(CLIENT_SOCK.sockfd, "PASS ", sizeof("PASS "), 0);
		client->accepted = 0;
	}
	return (EXIT_SUCCESS);
}

static int32_t		check_dupenick(t_servenv *server, t_action *act)
{
	int32_t		i;
	t_client	*client;

	i = 0;
	while (i < SRV_SOCK.nfds)
	{
		client = server->clients[i];
		if (client)
		{
			if (client->nickname && ft_strequ(client->nickname, act->comm + 1))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int32_t					ft_addnick(t_servenv *server, t_action *act)
{
	t_client	*client;

	client = SRV_CLIENT;
	if (param_split(act->comm + 1, act) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_dupenick(server, act) == EXIT_FAILURE)
	{
		send(CLIENT_SOCK.sockfd,
				"ERR_NICKCOLLISION", sizeof("ERR_NICKCOLLISION"), 0);
		return (EXIT_SUCCESS);
	}
	else
	{
		if (!(client->nickname = 
					(char *)ft_memalloc(ft_strlen(act->comm + 1) + 1))
			|| !ft_strcpy((act->comm + 1), client->nickname))
			return (EXIT_FAILURE);
		send(CLIENT_SOCK.sockfd, "NICK ", sizeof("NICK "), 0);
	}
	return (EXIT_SUCCESS);
}
