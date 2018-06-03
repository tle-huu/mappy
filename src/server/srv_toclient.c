/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_toclient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:33:47 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/02 16:22:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include "communication.h"

static int32_t	welcome(void)
{
	if (send(SRV_CLNT, "WELCOME\n", sizeof("WELCOME\n"), 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_srv_toclient	toclient = {
	&welcome
};
