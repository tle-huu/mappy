/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 18:45:10 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/02 04:22:47 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

t_player	*init_player(int sockfd, t_server *server)
{
	t_player *new;

	if (!(new = ft_memalloc(sizeof(t_player))))
		return (NULL);
	new->fd = sockfd;
	new->direction = rand_direction();
	new->see_range = 1;
	new->position = rand_position(server->map);
	new->lifetime = 1260;
	return (new);
}

int			init_server(t_server *server)
{
	if (!(server->players = ft_memalloc(sizeof(t_player *) * FD_SETSIZE)))
		return (EXIT_FAILURE);
	if (!(server->map = ft_memalloc(sizeof(t_map))))
	{
		free(server->players);
		return (EXIT_FAILURE);
	}
	if (!(server->events = init_pqueue()))
	{
		free(server->map);
		free(server->players);
		return (EXIT_FAILURE);
	}
	// server->time = 10;
	server->min_players = 1;
	return (EXIT_SUCCESS);
}
