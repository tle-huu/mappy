/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:46:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 19:56:03 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIVERSAL_H
# define UNIVERSAL_H

typedef struct			s_inventory
{
	uint64_t			items;
}						t_inventory;

typedef	struct			s_location
{
	int32_t				x;
	int32_t				y;
	int8_t				orientation;
}						t_location;

# endif
