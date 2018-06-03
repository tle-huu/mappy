/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 19:00:26 by nkouris          ###   ########.fr       */
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
#ifdef DEBUG
	ft_printf("<--- CLIENT INIT --->\n");
#endif
	if (!((SRV_TEMP.purgatory)[SRV_CLNT]))
	{
		if ((ret = communicate.toclient.welcome()) == EXIT_FAILURE)
			SRV_TEMP.purgatory[SRV_CLNT] = NOT_ACCEPTED;
	}
	else
	{
		if (player.islost())
			ret = player.add_toteam();
		else
		{
			ret = player.new();
			ret = player.add_toteam();
		}
	}
	return (ret);
}
