/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 13:51:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/07/15 17:57:36 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_num.h"
# include <stdio.h>

char		*ft_nuitoa_base(unsigned int n, int base, int length)
{
	static char	result[3];

	ft_bzero(result, 3);
	while (length)
	{
		result[--length] = BASEKEY[n % base];
		n =  n / base;
	}
	return (result);
}
