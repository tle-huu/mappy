/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 22:30:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"
#include "communication.h"
#include "player.h"


/* method function prototypes */
static int32_t	new(void);
static int32_t	isplayer(int32_t cl);
static void		del(int32_t cl);

/* method object */
t_client_methods	client = {
	&new,
	&isplayer,
	&del
};

static inline __attribute__((always_inline))void	add_fd_select(int32_t sock)
{
	printf("fd to add : <%d>\ncurrent nfds : <%d>\n", sock, SRV_SOCK.nfds);
	FD_SET(sock, SRV_SOCK.copy);
	if (SRV_SOCK.nfds <= sock)
		SRV_SOCK.nfds = (sock + 1);
}

static int32_t		new(void)
{
	int32_t	newfd;
	int32_t	ret;

	ret = EXIT_SUCCESS;
	printf("<--- NEW CLIENT --->\n");
	newfd = accept(SRV_SOCK.sockfd,
				(struct sockaddr *)&(SRV_SOCK.temp), &(SRV_SOCK.socklen));
	(SRV_ALLP.status)[newfd] = NOT_ACCEPTED;
	add_fd_select(newfd);
	if (!SRV_GENV.maxinitial_clients && !SRV_GENV.maxingame_players)
	{
		client.del(newfd);
		printf("Client %d rejected, not allowed\n", newfd);
	}
	else
		printf("New client %d connected\n", newfd);
	ret = communicate.toclient.outgoing(newfd, "WELCOME\n");
	return (ret);
}

static int32_t		isplayer(int32_t cl)
{
	int32_t	ret;

	ret = player.new(cl);
	ret = player.add_toteam(cl);
// check egg queue and egg status	
	return (ret);
}

static void			del(int32_t cl)
{
	printf("Remove client <%d> from fdset and lookup\n", cl);
	if (SRV_ALLP.lookup[cl])
	{
		if ((((SRV_ALLP.lookup)[cl])->team))
		{
			printf("Deleting reference to player in team\n");
			((((SRV_ALLP.lookup)[cl])->team)->players)[cl] = NULL;
		}
	}
	if ((SRV_ALLP.client_stat)[cl] != DEAD)
		SRV_GENV.maxclients++;
	(SRV_ALLP.client_stat)[cl] = 0;
	close(cl);
	FD_CLR(cl, SRV_SOCK.copy);
}
