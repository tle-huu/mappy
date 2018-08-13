/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:12:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/08 12:26:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_dblist	*ft_dblistnew(void *content, size_t content_size)
{
	t_dblist	*head;

	if (!(head = (t_dblist *)ft_memalloc(sizeof(t_dblist)))
		|| !(head->data = ft_memalloc(content_size)))
		return (0);
	if (!content)
		content_size = 0;
	head->data = ft_memmove(head->data, content, content_size);
	head->d_size = content_size;
	free(content);
	return (head);
}
