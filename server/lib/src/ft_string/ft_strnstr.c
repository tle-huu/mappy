/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 11:27:00 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/28 23:34:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static char		*if_occur(char *look, const char *find, size_t ind)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (look[i] && ind > 0)
	{
		if (find[j] == look[(i)])
		{
			while ((find[j] == look[(j + i)]) && (find[j]))
			{
				j++;
				if (find[j] == '\0' && j < (ind + 1))
					return (&look[i]);
			}
		}
		j = 0;
		i++;
		ind--;
	}
	return (0);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		l_len;
	int		b_len;
	char	*r_big;

	r_big = (char*)big;
	l_len = ft_strlen(little);
	b_len = ft_strlen(big);
	if (l_len == 0)
		return (r_big);
	else if (b_len < l_len)
		return (0);
	r_big = if_occur(r_big, little, len);
	return (r_big);
}
