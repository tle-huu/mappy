/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 13:51:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/07/14 12:02:41 by nkouris          ###   ########.fr       */
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

char		*ft_uitoa_base(unsigned int n, int base)
{
	int			length;
	static char	result[12];

	ft_bzero(result, 12);
	length = count_num_base(n, base);
	if (!n)
		result[0] = '0';
	while (n)
	{
		result[--length] = BASEKEY[n % base];
		n =  n / base;
	}
	return (result);
}
