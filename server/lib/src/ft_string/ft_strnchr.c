/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 12:57:34 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/08 02:46:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* finds the last occurence of a char in the given string */

#include "libft.h"

char	*ft_strnchr(const char *s, int c)
{
	char	n;
	char	*t;
	char	*ret;

	t = (char *)s;
	n = (char)c;
	while (*t)
	{
		if (*t == n)
			ret = t;
		t++;
	}
	if (!ret || !t)
		return (0);
	else
		return (ret);
}
