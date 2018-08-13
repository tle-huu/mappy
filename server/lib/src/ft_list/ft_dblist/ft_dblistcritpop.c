/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistcritpop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:34:07 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/15 14:38:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_dblist	*ft_dblistcritpop(t_dblist *node, int (*f)(void *))
{
	t_dblist	*hold;

	hold = node;
	while (hold)
	{
		if (f(hold->data))
		{
			//printf("%sQueued event removed%s\n", "\033[48;5;57m", "\033[0m");
			ft_dblistpop(hold);
			return (hold);
		}
		hold = hold->next;
	}
	return (NULL);
}
