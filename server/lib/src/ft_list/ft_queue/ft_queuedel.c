/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queuedel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:32:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/18 17:32:45 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_queuedel(t_queue *key, t_dblist *(*f)(t_dblist *del))
{
	t_dblist	*temp;

	temp = key->first;
	while (temp)
		temp = f(temp);
	free(key);
}
