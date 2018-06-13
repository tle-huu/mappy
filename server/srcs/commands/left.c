/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:49:25 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/12 07:13:29 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

int		command_left(t_player *player, t_server *serv)
{
	player->direction = (player->direction / 2 == 0) ? WEST : player->direction / 2;
	if (send(player->fd, MSG_OK, ft_strlen(MSG_OK), 0) == -1)
		return (error(0, "Send", false));
	return (EXIT_SUCCESS);

}
