/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popfront.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:26:00 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 16:36:43 by nkouris          ###   ########.fr       */
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

t_dblist	*ft_popfirst(t_queue *key)
{
	t_dblist	*temp;

	if (!key)
		return (0);
	else
	{
		if (key->first)
		{
			key->qlen ? key->qlen-- : key->qlen;
			temp = key->first;
			key->first = key->first->next;
			key->first ? key->first->prec = 0 : key->first;
			if (temp == key->last)
				key->last = key->first;
			temp->next = 0;
			return (temp);
		}
	}
	return (0);
}
