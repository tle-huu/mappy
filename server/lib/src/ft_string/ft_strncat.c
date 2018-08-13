/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 09:33:59 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/28 23:35:09 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char			*f_dst;
	const char		*c_dst;
	unsigned int	c_n;

	f_dst = dst;
	c_dst = (const char*)dst;
	c_n = ft_strlen(c_dst);
	dst += ft_strlen(c_dst);
	if (n > c_n && c_n != 0)
		n = c_n;
	while (n > 0)
	{
		*dst++ = *src++;
		n--;
	}
	*dst = '\0';
	return (f_dst);
}
