/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublistpop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:07:37 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:18:00 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_sublistpop(t_list **node, int (*f)(void *))
{
	t_list	*hold;
	t_list	*prev;
	t_list	*ret;

	hold = *node;
	prev = 0;
	ret = 0;
	while (hold)
	{
		if (f(hold->data))
		{
			if (hold == *node)
				*node = (*node)->next;
			else
				prev->next = hold->next;
			if (!ret)
				ret = hold;
			else
			{
				hold->next = ret;
				ret = hold;
			}
		}
		prev = hold;
		hold = hold->next;
	}
	return (ret ? ret : 0);
}

