/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 13:51:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/07/10 16:57:53 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_num.h"

static int		count_num_base(unsigned long n, unsigned long base)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static int	find_sign(int o)
{
	if (o < 0)
		return (1);
	else
		return (0);
}

char		*ft_itoa_base(int n, int base)
{
	int		length;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = count_num_base(n, base);
	result = ft_strnew(length);
	if (!result)
		return (NULL);
	else if (n == 0)
		result[0] = '0';
	if (find_sign(n))
	{
		result[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		result[--length] = BASEKEY[n % base];
		n =  n / base;
	}
	return (result);
}
