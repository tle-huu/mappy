/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_gets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:37:46 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 19:13:44 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_server.h"

int32_t		get_port(char **argv, __attribute__((unused))t_opts *opt)
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
	g_servenv->port = port;
	return (EXIT_SUCCESS);
}
