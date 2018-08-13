/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 15:13:06 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/18 17:31:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*c_dst;
	unsigned char	*c_src;

	i = 0;
	c_dst = (unsigned char*)dst;
	c_src = (unsigned char*)src;
	while (i++ < n)
	{
		*c_dst = *c_src;
		c_dst++;
		c_src++;
	}
	return (dst);
}
