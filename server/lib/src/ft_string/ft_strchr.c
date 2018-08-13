/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 12:57:34 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/04 13:48:19 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchr(const char *s, int c)
{
	char	n;
	char	*t;

	t = (char *)s;
	n = (char)c;
	if (*t == n)
		return (t);
	while ((*t) && *t != n)
	{
		t++;
	}
	if (*t == n)
		return (t);
	else
		return (0);
}
