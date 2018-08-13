/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:36:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/31 16:57:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* this implementation of get opts accepts an object of the style:
**	t_opt[] = {
**			"-[opt]:", [nparams], &handling_function,
**			|| "--[optstring]:", [nparams], &handling_function,
** 			etc
** 	}
** whose elements correspond to options that are valid in the calling program
** ft_getopts will return the position of an illegal option found and set
** optstring to NULL; it will return EXIT_SUCCESS and point opstring to the 
** corresponding valid
*/

#include "ft_getopts.h"

static inline __attribute__((always_inline)) int32_t	
			param_action(t_opts *opts, char **argv, int32_t *word)
{
	int32_t	i;

	i = 0;
	if (!(opts->nparams))
	{
		if (opts->handler(NULL, opts) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		(*word)++;
		if (!*(argv + *word)
			|| opts->handler((argv + *word), opts) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (opts->nparams > 1)
			*word += (opts->nparams - 1);
	}
	return (EXIT_SUCCESS);
}

static inline __attribute__((always_inline)) int32_t	
			match_opts(t_opts *opts, char **argv, int32_t *word)
{
	int32_t	i;

	i = 0;
	while (opts->opt)
	{
		if (ft_strequ(opts->opt, (argv[*word])))
		{
			if (param_action(opts, argv, word) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
				return (EXIT_SUCCESS);
		}
		opts++;
	}
	return (EXIT_FAILURE);
}

int32_t		ft_getopts(t_opts *opts, char **argv)
{
	int32_t	i;

	i = 1;
	while (argv[i])
	{
		while (IS_WHSPC(*(argv[i])))
			(argv[i])++;
		if (*(argv[i]) == '-')
		{
			(argv[i])++;
			if (*(argv[i]) == '-')
				(argv[i])++;
			if (match_opts(opts, argv, &i) == EXIT_FAILURE)
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (EXIT_SUCCESS);
}
