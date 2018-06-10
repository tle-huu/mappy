/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:31:32 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 22:35:44 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEATH_H
# define DEATH_H

typedef struct	s_expiration
{
	t_timeval	timesup;

}				t_expiration;

typedef	struct	s_deathtrack
{
	t_queue		eggs;

}				t_deathtrack;

#endif
