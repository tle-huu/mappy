/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 10:53:55 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/08 17:25:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int32_t	comparetime(t_timeval *comtime);
static void		cleartime(t_timeval *comtime);
static void		settimer(t_timeval **time);

t_server_methods server = {
	&comparetime,
	&cleartime,
	&settimer
};

static int32_t	comparetime(t_timeval *comtime)
{
	if (comtime->tv_sec >= SRV_TIME.tv_sec
		&& comtime->tv_usec >= SRV_TIME.tv_usec)
		return (1);
	return (0);
}

static void		cleartime(t_timeval *comtime)
{
	comtime->tv_sec = 0;
	comtime->tv_usec = 0;
}

static void		settimer(t_timeval **time)
{
	t_timeval	temp;

	gettimeofday(&temp, NULL);
	if (!(*time)
		|| (!((*time)->tv_sec) || !((*time)->tv_usec)))
		;
	else
	{
		(*time) = (t_timeval *)calloc(1, sizeof(t_timeval));
		(*time)->tv_sec = (*time)->tv_sec - temp.tv_sec;
		(*time)->tv_usec = (*time)->tv_usec - temp.tv_usec;
	}
}
