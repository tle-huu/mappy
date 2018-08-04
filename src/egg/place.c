/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 23:35:49 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/20 00:47:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "egg.h"

static int32_t		onboard(t_egg *egg);

__attribute__((constructor))void	construct_eggplace(void)
{
	egg.place.onboard = &onboard;
}

static int32_t		onboard(t_egg *eg)
{
	eg->location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	eg->location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	eg->location.orientation = 1 << arc4random_uniform((uint32_t)3);
	return (EXIT_SUCCESS);
}
