/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:25:39 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/27 17:21:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	c_s1;
	unsigned char	c_s2;

	i = 0;
	j = 1;
	while ((s1[i] || s2[i] != '\0') && (j++ <= n))
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			c_s1 = (unsigned char)s1[i];
			c_s2 = (unsigned char)s2[i];
			return (c_s1 - c_s2);
		}
	}
	return (0);
}
