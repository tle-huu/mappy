/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_sets2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:15:59 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/05 11:44:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.h"

int32_t		srv_settimeint(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	time;

	i = 0;
	if (!(time = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	SRV_GENV.timeint = time;
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
	SRV_GENV.maxclients = maxc;
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

