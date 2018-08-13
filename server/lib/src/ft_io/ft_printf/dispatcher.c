/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:04:31 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 15:35:57 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_conv(const char **format, t_flags *flags, va_list *args)
{
	if (**format == 's' || **format == 'S')
		conv_s(format, flags, args);
	else if (**format == 'p')
		conv_p(flags, args);
	else if (**format == 'd' || **format == 'D'
			|| **format == 'i')
		conv_d_i(format, flags, args);
	else if (**format == 'o' || **format == 'O')
		conv_o(format, flags, args);
	else if (**format == 'u' || **format == 'U')
		conv_u(format, flags, args);
	else if (**format == 'x' || **format == 'X')
		conv_x(format, flags, args);
	else if (**format == '%')
		conv_flag(flags);
	else if (**format == 'c' || **format == 'C')
		conv_c(flags, args);
	else if (**format == 'n')
		conv_n(flags, args);
	else
	{
		va_arg(*args, int);
		(*format)--;
	}
}

static void	clear_flags(t_flags *flags)
{
	flags->altform = 0;
	flags->zpad = 0;
	flags->negwidth = 0;
	flags->spacepad = 0;
	flags->preper = 0;
	flags->sign = 0;
	flags->printsign = 0;
	flags->ptox = 0;
	flags->fieldwidth = -1;
	flags->precision = -1;
	flags->lenmod[0] = 0;
	flags->pre = 0;
	flags->strx = 0;
	flags->stri = 0;
	flags->failure = 0;
	flags->ptox = 0;
	flags->wc = 0;
}

static void	naive_write(const char **format, t_flags *flags)
{
	int			i;
	const char	*naive;

	naive = (*format);
	i = 0;
	while (**format != '%' && **format)
	{
		(*format)++;
		i++;
	}
	if (i)
		buf_store(flags, i, naive, 0);
}

int			ft_printf(const char *format, ...)
{
	va_list			args;
	t_flags			flags;

	flags.n = 0;
	flags.failure = 0;
	va_start(args, format);
	while (*format)
	{
		if (!(flags.str = (char *)ft_memalloc(512 + 1)))
			return (-1);
		clear_flags(&flags);
		naive_write(&format, &flags);
		store_pre(&format, &flags, &args);
		parse_conv(&format, &flags, &args);
		if (kill_switch(&flags))
			break ;
		*format ? format++ : format;
		write(1, flags.str, flags.strx);
		flags.n += flags.strx;
		flags.wc ? flags.n -= 1 : flags.n;
		ft_memdel((void **)(&(flags.str)));
	}
	va_end(args);
	return (flags.failure ? -1 : flags.n);
}
