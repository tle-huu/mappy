/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 17:17:15 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/28 23:57:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	ft_strdel(char **as)
{
	void **pass;

	if (!as)
		return ;
	pass = (void**)as;
	ft_memdel(pass);
	as = 0;
}
