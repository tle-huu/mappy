/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 12:02:45 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/29 00:32:18 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	if (s == 0)
		return (0);
	i = 0;
	len = ft_strlen(s);
	len--;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (i < len && (s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len--;
	new = ft_strnew((len - i) + 1);
	if (new)
	{
		j = 0;
		while (i <= len)
			new[j++] = s[i++];
		new[j] = '\0';
		return (new);
	}
	else
		return (0);
}
