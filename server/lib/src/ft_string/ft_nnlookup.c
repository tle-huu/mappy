/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:54:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:48:46 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static int		if_occur(char *look, const char *find, size_t ind, char b)
{
	unsigned int i;
	unsigned int j;
	unsigned int nind;

	i = 0;
	j = 0;
	nind = ind;
	while (look[i])
	{
		if (find[j] == look[i])
		{
			while ((find[j] == look[(j + i)]) && (find[j]) && ind > 0)
			{
				j++;
				if (find[j] == b)
					return (1);
				ind--;
			}
		}
		ind = nind;
		j = 0;
		i++;
	}
	return (0);
}

int				ft_nlookup(char *key, const char *str, size_t len, char b)
{
	int		slen;
	int		klen;

	slen = ft_strlen(str);
	klen = ft_strlen(key);
	if (slen == 0)
		return (1);
	else if (klen < slen)
		return (0);
	return (if_occur(key, str, len, b));
}
