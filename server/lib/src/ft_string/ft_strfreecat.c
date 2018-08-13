/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfreecat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 18:51:30 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/07 19:54:07 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strfreecat(char *dst, char *src)
{
	char *f_dst;
	char *src_cpy;

	f_dst = dst;
	src_cpy = src;
	dst += ft_strlen(dst);
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	free(src_cpy);
	return (f_dst);
}
