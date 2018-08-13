/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 15:52:29 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/26 19:57:55 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*c_s;
	unsigned char	cmp;

	i = 0;
	c_s = (unsigned char*)s;
	cmp = (unsigned char)c;
	while (n-- > 0)
	{
		if (*c_s == cmp)
		{
			c_s = &(*c_s);
			return (c_s);
		}
		c_s++;
	}
	return (0);
}
