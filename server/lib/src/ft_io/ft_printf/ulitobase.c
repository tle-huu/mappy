/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulitobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:31:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 15:35:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_num_signed(long long n, long base)
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

int		count_num(unsigned long n, unsigned long base)
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

int		base_conv_signed(long long n, char *address, long base, int len)
{
	int relen;
	int baselen;

	relen = 0;
	baselen = count_num_signed(n, base);
	len != baselen ? len = baselen : len;
	if (!n)
	{
		address[0] = '0';
		relen++;
	}
	if (n == LONG_MIN)
		relen = base_conv(MINLONG_SAFE, address, 10, 19);
	else
	{
		n < 0 ? n = n * -1 : n;
		while (n)
		{
			address[--len] = BASE_FLAGS[n % base];
			n = n / base;
			relen++;
		}
	}
	return (relen);
}

int		base_conv(unsigned long n, char *address, unsigned long base, int len)
{
	int relen;
	int baselen;

	relen = 0;
	baselen = count_num(n, base);
	if (baselen != len)
		len = baselen;
	if (!n)
	{
		address[0] = '0';
		relen++;
	}
	while (n)
	{
		address[--len] = BASE_FLAGS[n % base];
		n = n / base;
		relen++;
	}
	return (relen);
}
