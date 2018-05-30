/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_client_comm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 11:19:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:51:09 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int	(*command[])(t_servenv *, t_action *) = {
			0,
			ft_passconfirm,
			ft_addnick,
			ft_joinchannel,
			ft_chanmessage,
			ft_usnmessage
};

int32_t		server_client_comm(t_client *client, t_servenv *server)
{
	char		buf[513];
	t_action	act;
	int16_t		act_num;

#ifdef DEBUG
	ft_printf("\tclient -> server communication\n");
#endif
	ft_bzero(buf, 513);
	ft_bzero(&act, sizeof(t_action));
	recv(CLIENT_SOCK.sockfd, buf, sizeof(buf), 0);
	if (!(act_num = comm_split(buf, &act)))
		return (EXIT_FAILURE);
#ifdef DEBUG
	ft_printf("client sent: %s, act_num : %d\n", buf, act_num);
#endif
	if (command[act_num](server, &act) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
