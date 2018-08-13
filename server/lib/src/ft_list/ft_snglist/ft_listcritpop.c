/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listcritpop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:07:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:17:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_listcritpop(t_list **node, int (*f)(void *))
{
	t_list	*hold;
	t_list	*prev;

	hold = *node;
	prev = 0;
	while (hold)
	{
		if (f(hold->data))
		{
			if (hold == *node)
				*node = (*node)->next;
			else
				prev->next = hold->next;
			return (hold);
		}
		prev = hold;
		hold = hold->next;
	}
	return (0);
}
