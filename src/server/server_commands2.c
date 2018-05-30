/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_commands2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:46:40 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:50:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static inline __attribute__((always_inline))int32_t	concat_gen(char **concat,
		t_client *client, t_action *act, char *cmd)
{
	if (!(*concat = (char *)ft_memalloc(ft_strlen(cmd)
					+ act->message_len + ft_strlen(client->nickname) + 2)))
		return (EXIT_FAILURE);
	ft_strcpy(*concat, cmd);
	ft_strcat(*concat, (client->nickname));
	ft_strcat(*concat, " ");
	ft_strcat(*concat, act->message);
	if (act->param)
		*(act->param) = '\0';
	return (EXIT_SUCCESS);
}

int32_t		ft_chanmessage(t_servenv *server, t_action *act)
{
	t_client	*client;
	char		*concat;
	int32_t		i;

	client = SRV_CLIENT;
	i = 0;
	message_split((act->comm + 1), act);
	concat_gen(&concat, client, act, "MSG ");
#ifdef DEBUG
	ft_printf("concat : %s\n", concat);
#endif
	if (!(client->chanp))
		send(CLIENT_SOCK.sockfd, "ERR_JOINCHANNEL ", sizeof("ERR_JOINCHANNEL "), 0);
	else
	{
		while (i <= SRV_SOCK.nfds)
		{
			if (((client->chanp)->clients)[i])
				send((((client->chanp)->clients)[i])->csock.sockfd,
						concat, ft_strlen(concat), 0);
			i++;
		}
	}
	free(concat);
	return (EXIT_SUCCESS);
}

int32_t		ft_usnmessage(t_servenv *server, t_action *act)
{
	t_client	*client;
	char		*concat;
	int32_t		i;

	client = SRV_CLIENT;
	i = 0;
	usn_split((act->comm + 1), act);
	message_split((act->param + 1), act);
	concat_gen(&concat, client, act, "PRVMSG ");
#ifdef DEBUG
	ft_printf("concat : %s\n", concat);
#endif
	while (i <= SRV_SOCK.nfds)
	{
		if (ft_strequ((server->clients[i])->nickname, (act->comm + 1)))
		{
			send((server->clients[i])->csock.sockfd, concat, ft_strlen(concat), 0);
			break ;
		}
		i++;
	}
	if (i > SRV_SOCK.nfds)
		send(CLIENT_SOCK.sockfd, "ERR_NOSUCHNICK ", sizeof("ERR_NOSUCHNICK "), 0);
	free(concat);
	return (EXIT_SUCCESS);
}
