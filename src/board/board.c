/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 10:45:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 12:18:13 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "board.h"
#include "communication.h"

/* method function prototypes */
static int32_t	send_dimens(int32_t cl);
static int32_t	new(void);

/* method object */
t_board_methods	board = {
	&new,
	&send_dimens
};

static int32_t	new(void)
{
	return (EXIT_SUCCESS);
}

static int32_t	send_dimens(int32_t cl)
{
	char	*num;
	char	*str;
	int32_t	nlen;

	nlen = ft_numlen(SRV_BORD.x);
	nlen += ft_numlen(SRV_BORD.y);
	nlen += 2;
	if ((!(num = ft_itoa(SRV_BORD.x)))
		|| !(str = (char *)calloc(1, (nlen + 1)))
		|| !(str = strcat(str, num)))
		return (EXIT_FAILURE);
	free(num);
	if (!(str = strcat(str, " "))
		|| !(num = ft_itoa(SRV_BORD.y))
		|| !(str = strcat(str, num))
		|| !(str = strcat(str, "\n"))
		|| !(communicate.toclient.outgoing(cl, str)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
