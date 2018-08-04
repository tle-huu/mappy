/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:10:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 22:53:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/*
**	srv_sets
*/

int32_t		srv_setboardx(char **argv, __attribute__((unused))t_opts *opt);
int32_t		srv_setboardy(char **argv, __attribute__((unused))t_opts *opt);
int32_t		srv_setport(char **argv, t_opts *opt);
int32_t		srv_setteams(char **argv, t_opts *opt);
int32_t		srv_setmaxclients(char **argv, t_opts *opt);
int32_t		srv_settimeint(char **argv, __attribute__((unused))t_opts *opt);

/*
**	error
*/

void		usage_warning(char *str);

/*
**	client_init
*/

int32_t		client_init(void);
int32_t		game_io(void);

#endif
