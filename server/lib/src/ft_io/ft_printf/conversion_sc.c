/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_sc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:17:55 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 15:36:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_s_null(t_flags *flags)
{
	int pad;
	int empty;

	empty = 0;
	pad = print_padding(flags, &empty);
	buf_store(flags, 6, "(null)", 0);
	if (pad > 0)
		buf_store(flags, pad, 0, ' ');
}

static void	conv_ws(t_flags *flags, wchar_t *str)
{
	int				i;
	int				j;
	int				pad;
	unsigned char	*ustr;

	i = 0;
	pad = 0;
	while (str[i])
		i++;
	ustr = (unsigned char *)ft_memalloc((unsigned int)i);
	j = 0;
	while (j < i)
	{
		if (*str <= 255)
			ustr[j++] = (unsigned char)(*str++);
		else
			j++;
	}
	if (flags->fieldwidth >= 0 || flags->precision >= 0)
		pad = print_padding(flags, &i);
	buf_store(flags, i, (const char *)ustr, 0);
	if (pad > 0)
		buf_store(flags, pad, 0, ' ');
	ft_memdel((void **)(&(ustr)));
}

void		conv_s(const char **format, t_flags *flags, va_list *args)
{
	int				strlen;
	int				pad;
	char			*str;
	wchar_t			*wstr;

	pad = -1;
	wstr = 0;
	str = 0;
	if (flags->lenmod[0] == 'l' || **format == 'S')
		wstr = va_arg(*args, wchar_t *);
	else
		str = va_arg(*args, char *);
	if (!str && !wstr)
		conv_s_null(flags);
	else if (str)
	{
		strlen = ft_strlen((const char *)str);
		if (flags->fieldwidth > strlen || flags->precision >= 0)
			pad = print_padding(flags, &strlen);
		buf_store(flags, strlen, str, 0);
		if (pad > 0)
			buf_store(flags, pad, 0, ' ');
	}
	else
		conv_ws(flags, wstr);
}

void		conv_c(t_flags *flags, va_list *args)
{
	int				pad;
	unsigned int	nchar;
	wint_t			wchar;
	int				single;

	pad = 0;
	single = 1;
	if (flags->lenmod[0] == 'l')
	{
		wchar = va_arg(*args, wint_t);
		nchar = (unsigned int)wchar;
	}
	else
		nchar = va_arg(*args, unsigned int);
	nchar > 127 || !nchar ? flags->wc = 1 : flags->wc;
	pad = print_padding(flags, &single);
	if (!nchar)
	{
		flags->strx++;
		flags->n++;
	}
	buf_store(flags, ((!nchar) ? (0) : (1)), 0, nchar);
	if (pad > 0)
		buf_store(flags, pad, 0, ' ');
}

void		conv_flag(t_flags *flags)
{
	int pad;

	pad = 0;
	flags->preper = 0;
	flags->precision = 0;
	flags->zpad && flags->negwidth ? flags->zpad = 0 : flags->zpad;
	pad = print_padding_num(flags, 1, 0);
	buf_store(flags, 1, 0, '%');
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, 1, 0);
	}
}
