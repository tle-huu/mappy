/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 15:35:29 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/11 14:58:17 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*c_src;
	unsigned char	*c_dst;

	i = 0;
	c_src = (unsigned char *)src;
	c_dst = (unsigned char *)dst;
	if (dst < src)
	{
		while (i++ < len)
			*c_dst++ = *c_src++;
	}
	else if (dst > src)
	{
		while (len-- > 0)
			c_dst[len] = c_src[len];
	}
	return (dst);
}
