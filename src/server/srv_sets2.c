/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_sets2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:15:59 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/14 11:19:52 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "server.h"

#define TEAM ((g_servenv->teams)[i])

int32_t		srv_settimeint(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	timeint;

	i = 0;
	if (!(timeint = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	SRV_GENV.timeinterval = timeint;
	return (EXIT_SUCCESS);
}

int32_t		srv_setmaxclients(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	maxc;

	i = 0;
	if (!(maxc = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	SRV_GENV.maxinitial_clients = maxc * SRV_GENV.nteams;
	i = 0;
	while (i < SRV_GENV.nteams)
	{
		TEAM.nplayers = maxc;
		i++;
	}
	return (EXIT_SUCCESS);
}

int32_t		srv_setport(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	port;

	i = 0;
	if (!(port = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	SRV_SOCK.port = port;
	return (EXIT_SUCCESS);
}

