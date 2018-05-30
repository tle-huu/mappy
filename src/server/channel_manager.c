/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 11:04:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:50:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

void		user_addtochannel(t_servenv *server, t_channel *channel)
{
	t_client	*client;

#ifdef DEBUG
	ft_printf("chan <%p>\n", channel);
#endif
	client = SRV_CLIENT;
	client->chanp = channel;
	(channel->clients)[server->curr_client] = client;
	send(CLIENT_SOCK.sockfd, "JOIN ", sizeof("JOIN "), 0);
#ifdef DEBUG
	ft_printf("user added, message sent\n", channel);
#endif
}

int32_t		check_dupchannel(t_servenv *server, t_action *act)
{
	t_dblist	*temp_list;
	t_channel	*temp_chan;

	if (!server->channels)
	{
		if (new_channel(server, act) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	temp_list = server->channels;
	while (temp_list)
	{
		temp_chan = (t_channel *)((temp_list)->data);
		if (ft_strequ(temp_chan->name, (act->comm + 1)))
		{
			user_addtochannel(server, temp_chan);
			return (EXIT_SUCCESS);
		}
		temp_list = temp_list->next;
	}
	return (-1);
}

int32_t		new_channel(t_servenv *server, t_action *act)
{
	t_channel	*chan;

	if (!(chan = (t_channel *)ft_memalloc(sizeof(t_channel)))
		|| !(chan->name = ft_strdup(act->comm + 1))
		|| !(chan->clients = (t_client **)ft_memalloc(sizeof(t_client *) * FD_SETSIZE))
		|| !(server->channels = ft_dblistnew(chan, sizeof(t_channel))))
		return (EXIT_FAILURE);
	user_addtochannel(server, (t_channel *)((server->channels)->data));
	return (EXIT_SUCCESS);
}
