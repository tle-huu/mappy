/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 13:51:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/09 21:46:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_num.h"

static int	itoa_count_num(int p)
{
	int len;

	len = 0;
	if (p < 0)
	{
		len++;
		p = (p * -1);
	}
	else if (p == 0)
		return (1);
	while (p != 0)
	{
		p = p / 10;
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

char		*ft_itoa(int n)
{
	int			length;
	static char	result[12];

	ft_bzero(result, 12);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = itoa_count_num(n);
	if (n == 0)
		result[0] = '0';
	if (find_sign(n))
	{
		result[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		result[--length] = ((n % 10) + '0');
		n = (n - (n % 10)) / 10;
	}
	return (result);
}
