/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 17:52:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/29 00:00:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	length;
	unsigned int	i;
	char			*new;

	if (!s)
		return (0);
	i = 0;
	length = ft_strlen(s);
	new = ft_strnew(length);
	if (!new)
		return (0);
	while (i < length)
	{
		new[i] = f(s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
