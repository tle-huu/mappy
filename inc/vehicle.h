/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:30:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:34:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H


typedef struct		s_vehiclepool
{
	t_queue			*data;
	int32_t			(*new)(void);
	t_dblist		*(*pop)(void);
	void			(*add)(t_vehicle *add);
}					t_vehiclepool;

typedef struct		s_vehicleplace
{
	void			(*onboard)(t_vehicle *);
	void			(*advance)(t_vehicle *);
}					t_vehicleplace;

typedef struct		s_vehicle_methods
{
	t_vehiclepool	pool;
	t_vehicleplace	place;
	int32_t			(*new)(int32_t);
	int32_t			(*command)(t_vehicle *);
}					t_vehicle_methods;

t_vehicle_methods	vehicle;

#endif
