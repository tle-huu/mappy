/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopts.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:25:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 19:13:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPTS_H
# define FT_GETOPTS_H

# include "libft.h"

typedef	struct	s_opts
{
	char		*opt;
	int32_t		nparams;
	int32_t		(*handler)(char **, struct s_opts *);
}				t_opts;

int32_t		ft_getopts(t_opts *opts, char **argv);

#endif
