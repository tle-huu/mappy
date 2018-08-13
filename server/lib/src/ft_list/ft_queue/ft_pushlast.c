/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:24:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:17:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/*
**		Using a doubly linked list, as defined in libft.h
**				|
**				first -> (next)
**				(next)
**				.
**				.
**				.
**				.
**				.
**				(prec)
**				last -> (prec)
**				|
*/

void		ft_pushlast(t_queue *key, t_dblist *data)
{
	t_dblist	*temp;

	if (key)
	{
		key->qlen++;
		if (!key->last)
		{
			key->last = data;
			data->prec = key->first;
			key->first->next = data;
		}
		else
		{
			temp = key->last;
			data->prec = temp;
			data->next = 0;
			temp->next = data;
			key->last = data;
		}
	}
}
