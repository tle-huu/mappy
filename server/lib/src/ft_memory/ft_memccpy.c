/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 15:13:06 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/28 23:14:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int			i;
	unsigned char			*c_dst;
	unsigned char const		*c_src;
	unsigned char			c_c;

	i = 0;
	c_dst = (unsigned char*)dst;
	c_src = (unsigned const char *)src;
	c_c = (unsigned char)c;
	while (i < n)
	{
		if (c_src[i] == c_c)
		{
			c_dst[i] = c_src[i];
			i++;
			c_dst = &(c_dst[i]);
			return (c_dst);
		}
		c_dst[i] = c_src[i];
		i++;
	}
	return (0);
}
