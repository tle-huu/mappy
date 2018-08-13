/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:58:21 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/27 11:36:03 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strdup(const char *str)
{
	int		len;
	int		i;
	char	*c_str;

	i = 0;
	len = ft_strlen(str);
	c_str = (char*)malloc((len + 1));
	if (!c_str)
		return (0);
	c_str = ft_strcpy(c_str, str);
	return (c_str);
}
