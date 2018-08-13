/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:54:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/08 02:46:03 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
**	Usage:	look = delimited string with values for lookup
**			find = string in which to look for "key" values
**			len = maxlen of "key" keywords, to reduce coincidental substr matches
**			b = delimiter in key, which will keep count for match enum
*/

static int		if_occur(char *key, const char *look, size_t ind, char b)
{
	unsigned int i;
	unsigned int j;
	unsigned int nind;
	unsigned int nkey;

	i = 0;
	j = 0;
	nind = ind;
	nkey = 1;
	while (key[i])
	{
		if (look[j] == key[i])
		{
			while ((look[j] == key[(j + i)]) && (look[j]) && ind > 0)
			{
				j++;
				if (key[(j + i)] == b)
					return (nkey);
				ind--;
			}
		}
		if (key[i] == b)
			nkey++;
		ind = nind;
		j = 0;
		i++;
	}
	return (0);
}

/*
**	Usage:	key = delimited string with values for lookup
**			str = string in which to look for "key" values
**			len = maxlen of "key" keywords, to reduce coincidental substr matches
**			b = delimiter in key, which will keep count for match enum
*/

int				ft_nlookup(char *key, const char *str, size_t len, char b)
{
	int		slen;
	int		klen;

	slen = ft_strlen(str);
	klen = ft_strlen(key);
	if (slen == 0)
		return (1);
	return (if_occur(key, str, len, b));
}
