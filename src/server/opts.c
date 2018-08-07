/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:44:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/06 22:25:50 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "board.h"

static int32_t		boardload(char **argv, __attribute__((unused))t_opts *opt);
static int32_t		boardx(char **argv, __attribute__((unused))t_opts *opt);
static int32_t		boardy(char **argv, __attribute__((unused))t_opts *opt);
static int32_t		timeinterval(char **argv, __attribute__((unused))t_opts *opt);
static int32_t		maxclients(char **argv, __attribute__((unused))t_opts *opt);
static int32_t		port(char **argv, __attribute__((unused))t_opts *opt);

void		__attribute((constructor))construct_servergetopts(void)
{
	server.opts.boardType = UNKNOWNMAP;
	server.opts.boardload = &boardload;
	server.opts.boardx = &boardx;
	server.opts.boardy = &boardy;
	server.opts.timeinterval = &timeinterval;
	server.opts.maxclients = &maxclients;
	server.opts.port = &port;
}

static int32_t		boardload(char **argv, __attribute__((unused))t_opts *opt)
{
	if (server.opts.boardType == XYMAP)
		return (EXIT_SUCCESS);
	server.opts.boardType = LOADMAP;
	board.data.filename = strdup(*argv);
	return (EXIT_SUCCESS);
}

static int32_t		boardx(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	width;

	i = 0;
	if (server.opts.boardType == LOADMAP)
		return (EXIT_SUCCESS);
	
	server.opts.boardType = XYMAP;
	if (!(width = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	board.data.x = width - 1;
	return (EXIT_SUCCESS);
}

static int32_t		boardy(char **argv, __attribute__((unused))t_opts *opt)
{
	int32_t	i;
	int32_t	height;

	i = 0;
	if (server.opts.boardType == LOADMAP)
		return (EXIT_SUCCESS);

	server.opts.boardType = XYMAP;
	if (!(height = ft_atoi(*argv)))
	{
		while ((*argv)[i] == '0')
			i++;
		if ((*argv)[i])
		{
			ft_printf("Invalid parameter: %s\n", *argv);
			return (EXIT_FAILURE);
		}
	}
	board.data.y = height - 1;
	return (EXIT_SUCCESS);
}

static int32_t		timeinterval(char **argv, __attribute__((unused))t_opts *opt)
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
	server.simenv.timeinterval = timeint;
	return (EXIT_SUCCESS);
}

static int32_t		maxclients(char **argv, __attribute__((unused))t_opts *opt)
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
	server.simenv.maxinitial_clients = maxc;
	return (EXIT_SUCCESS);
}

static int32_t		port(char **argv, __attribute__((unused))t_opts *opt)
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
	ft_socket.port = port;
	return (EXIT_SUCCESS);
}
