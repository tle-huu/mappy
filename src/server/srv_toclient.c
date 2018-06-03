/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_toclient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:33:47 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 18:58:04 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "communication.h"

/* method function prototypes */
static int32_t	welcome(void);

t_communicate communicate = {
	/* methods */
	{
		&welcome
	}
};


//communicate.toclient.welcome = &welcome;


static int32_t	welcome(void)
{
	ft_printf("sizeof : %d \t strlen : %d\n", sizeof("WELCOME!\n"), strlen("WELCOME!\n"));
	if (send(SRV_CLNT, "WELCOME!\n", strlen("WELCOME!\n"), 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
