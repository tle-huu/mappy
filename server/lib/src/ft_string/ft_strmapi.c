/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 18:21:34 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/29 00:01:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		length;
	int		i;
	char	*new;

	if (!s)
		return (0);
	i = 0;
	length = ft_strlen(s);
	new = ft_strnew(length);
	if (!new)
		return (0);
	while (i < length)
	{
		new[i] = f(i, *s++);
		i++;
	}
	return (new);
}
