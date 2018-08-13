/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 13:00:13 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/27 16:01:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	n;
	char	*t;

	i = ft_strlen(s);
	t = (char *)s;
	n = (char)c;
	while (i > 0)
	{
		if (t[i] == n)
			return (&t[i]);
		i--;
	}
	if (t[i] == n)
		return (&t[i]);
	else
		return (0);
}
