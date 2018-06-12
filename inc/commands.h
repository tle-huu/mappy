/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:21:54 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 19:56:02 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define NCOMMANDS 1
# define EATCOMMAND 1
# define EGGCOMMAND 2

"command string, action to do, timing factor for setting alarm"
typedef struct	s_commhold
{
	char		*str;
	int32_t		(*action)(void *);
	float		factor;
}				t_commhold;

typedef struct			s_command
{
	t_timeval			alarm;
	int32_t				(*action)(void *);
	void				*entity;
	t_dblist			*container;
}						t_command;

typedef struct	s_command_methods
{
	int32_t		(*lookup)(int32_t);
	int32_t		(*add)(t_commhold *, int32_t);
	void		(*fail)(int32_t);
}				t_command_methods;

extern t_command_methods	commands;
extern t_commhold			commandlookup[1];

#endif
