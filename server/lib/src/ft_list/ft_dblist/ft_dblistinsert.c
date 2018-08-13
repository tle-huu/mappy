/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistinsert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:00:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/15 11:18:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_dblistinsert(t_dblist *current, t_dblist *insert)
{
	t_dblist	*temp;

	temp = current->prec;
	temp->next = insert;
	insert->prec = temp;
	current->prec = insert;
	insert->next = current;
}
