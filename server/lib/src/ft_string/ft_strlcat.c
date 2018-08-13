/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:52:56 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/27 15:24:04 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	d_len;
	unsigned int	s_len;
	unsigned int	i;
	const char		*c_dst;

	i = 0;
	c_dst = (const char *)dst;
	s_len = ft_strlen(src);
	d_len = ft_strlen(c_dst);
	if (size <= d_len)
		return (s_len + size);
	while ((dst[i]) && i < (size - 1))
		i++;
	while (i < (size - 1) && (src))
		dst[i++] = *src++;
	dst[i] = '\0';
	return (d_len + s_len);
}
