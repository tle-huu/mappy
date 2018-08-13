/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushfront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:22:50 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:17:20 by nkouris          ###   ########.fr       */
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

void		ft_pushfirst(t_queue *key, t_dblist *data)
{
	t_dblist	*temp;

	if (key)
	{
		key->qlen++;
		if (!key->first)
		{
			key->first = data;
			key->last = data;
		}
		else
		{
			temp = key->first;
			data->next = temp;
			data->prec = 0;
			temp->prec = data;
			key->first = data;
		}
	}
}
