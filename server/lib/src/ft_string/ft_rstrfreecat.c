/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfreecat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 18:51:30 by nkouris           #+#    #+#             */
/*   Updated: 2018/07/11 19:26:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_rstrfreecat(char *dst, char *src)
{
	char *f_dst;
	char *src_cpy;
	int32_t	src_len;

	f_dst = dst;
	src_cpy = src;
	dst += ft_strlen(dst);
	src_len = ft_strlen(src);
	while (src_len-- > 0)
		*dst++ = src[src_len];
	*dst = '\0';
	free(src_cpy);
	return (f_dst);
}
