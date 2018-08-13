/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:06:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:17:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_listadd(t_list **alst, void *content, size_t content_size)
{
	t_list	*new;

	if (!*alst)
	{
		*alst = ft_listnew(content, content_size);
		return;
	}
	new = ft_listnew(content, content_size);
	new->next = *alst;
	*alst = new;
}
