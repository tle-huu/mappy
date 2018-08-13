/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:55:31 by nkouris           #+#    #+#             */
/*   Updated: 2017/11/07 16:52:19 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*new;
	char	*c_s1;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	c_s1 = (char*)s1;
	new = ft_strnew((len1 + len2));
	if (!new)
		return (0);
	while (len1-- >= 0)
		new[i++] = *s1++;
	new = ft_strcat(new, s2);
	return (new);
}
