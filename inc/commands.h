/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:21:54 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 17:39:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

typedef struct	s_commhold
{
	char		*str;
	int32_t		(*action)(int32_t);
	float		factor;
}				t_commhold;

typedef struct	s_command_methods
{
	int32_t		(*lookup)(int32_t);
	int32_t		(*add)(t_commhold *, int32_t);
	void		(*fail)(int32_t);
}				t_command_methods;

extern t_command_methods	commands;
extern t_commhold			commandlookup[1];

#endif
