/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistpop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:37:10 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/08 15:05:29 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_dblist	*ft_dblistpop(t_dblist *node)
{
	t_dblist	*tprec;
	t_dblist	*tnext;

	tprec = node->prec;
	tnext = node->next;
	node->next = 0;
	node->prec = 0;
	if (tprec)
		tprec->next = tnext;
	if (tnext)
		tnext->prec = tprec;
	return (tnext);
}
