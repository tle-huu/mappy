/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/04 19:05:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "communication.h"
#include "player.h"
//#include "client.h"


///* method function prototypes */
//static int32_t	new
/* method object */

int32_t			client_init(void)
{
	int32_t		ret;

	ret = EXIT_SUCCESS;
	printf("<--- CLIENT INIT --->\n");
	if (!((SRV_TEMP.purgatory)[SRV_CLNT]))
	{
		ret = communicate.toclient.message("WELCOME\n");
		(SRV_TEMP.purgatory)[SRV_CLNT] = NOT_ACCEPTED;
	}
	else
	{
		if (player.islost(SRV_CLNT))
		{
			printf("Player is lost\n");
			ret = player.add_toteam(SRV_CLNT);
		}
		else
		{
			ret = player.new(SRV_CLNT);
			ret = player.add_toteam(SRV_CLNT);
		}
	}
	return (ret);
}
