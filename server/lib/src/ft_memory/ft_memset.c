/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:50:10 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/10 12:35:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cpy;
	unsigned int	i;

	i = 0;
	cpy = b;
	while (i < len)
		cpy[i++] = c;
	return (cpy);
}
