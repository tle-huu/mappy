/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:46:33 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 16:48:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_dblist	*ft_middel(t_queue *key, t_dblist *remove)
{
	if (key->first == remove)
		return (ft_popfirst(key));
	else if (key->last == remove)
		return (ft_poplast(key));
	return (ft_dblistpop(remove));
}
