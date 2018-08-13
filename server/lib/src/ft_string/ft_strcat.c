/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 18:50:21 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/07 18:51:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strcat(char *dst, const char *src)
{
	char *f_dst;

	f_dst = dst;
	dst += ft_strlen(dst);
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	return (f_dst);
}
