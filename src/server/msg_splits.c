/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mssg_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 10:16:45 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:51:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

inline __attribute__((always_inline))void		message_split(char *buf,
														t_action *act)
{
	act->message = buf;
	act->message_len = ft_strlen(buf);
}

inline __attribute__((always_inline))int32_t	usn_split(char *buf,
														t_action *act)
{
	if (ft_strchr(buf, ' '))
	{
		act->param = ft_strchr(buf, ' ');
		act->param_len = act->param - act->comm;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

inline __attribute__((always_inline))int32_t	param_split(char *buf,
														t_action *act)
{
	if (ft_strchr(buf, ' '))
		return (EXIT_FAILURE);
	act->param_len = ft_strlen(buf);
#ifdef DEBUG
	ft_printf("paramlen : %d param : \"%s\"\n", act->param_len, buf);
#endif
	return (EXIT_SUCCESS);
}

inline __attribute__((always_inline))int32_t	comm_split(char *buf,
														t_action *act)
{
	int16_t	res;

	res = 0;
	act->comm = ft_strchr(buf, ' ');
	act->comm_len = act->comm - buf;
	*(act->comm) = '\0';
	res = ft_nlookup(KEY, buf, 7, ' ');
#ifdef DEBUG
	ft_printf("commlen : %d command : %s retnum : %d\n", act->comm_len, buf, res);
#endif
	*(act->comm) = ' ';
	return (res);
}
