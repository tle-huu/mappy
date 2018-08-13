/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:37:30 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/13 18:53:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_num.h"

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' ||
			c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int		ft_skip_spaces(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' ||
			str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	return (i);
}

int		ft_atoi(const char *str)
{
	int sign;
	int j;
	int i;

	sign = 1;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		i = ft_skip_spaces(str);
		if (str[i] == '-')
		{
			sign = -1;
			i++;
		}
		else if (str[i] == '+')
			i++;
		while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		{
			j = (j * 10) + (str[i] - 48);
			i++;
		}
		return (j * sign);
	}
	return (0);
}
