/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:07:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:17:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_listnew(void *content, size_t content_size)
{
	t_list	*head;

	if (!(head = (t_list *)ft_memalloc(sizeof(t_list))))
		exit (0);
	if (!(head = (t_list *)ft_memalloc(sizeof(t_list)))
		|| !(head->data = ft_memalloc(content_size)))
		return (0);
	if (!content)
		content_size = 0;
	head->data = ft_memmove(head->data, content, content_size);
	head->d_size = content_size;
	return (head);
}
