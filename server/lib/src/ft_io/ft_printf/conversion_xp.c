/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_xp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 15:36:03 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_x_write(t_flags *flags, char *str, int relen, int numlen)
{
	int		pad;

	relen = 0;
	if (flags->altform)
		numlen += 2;
	if (flags->zpad && flags->altform)
		buf_store(flags, 2, flags->pre, 0);
	pad = print_padding_num(flags, numlen, 0);
	if (!flags->zpad && flags->altform)
		buf_store(flags, 2, flags->pre, 0);
	flags->altform ? numlen -= 2 : numlen;
	buf_store(flags, numlen, str, 0);
	flags->altform ? numlen += 2 : numlen;
	if (pad > 0)
	{
		flags->negwidth = 0;
		print_padding_num(flags, numlen, 0);
	}
}

void		conv_p(t_flags *flags, va_list *args)
{
	char *pass;
	char set;

	flags->lenmod[0] = 'l';
	set = 'x';
	pass = &set;
	flags->ptox = 1;
	flags->altform = 1;
	conv_x((const char **)&pass, flags, args);
}

void		conv_x(const char **format, t_flags *flags, va_list *args)
{
	char			str[64];
	unsigned long	num;
	int				relen;
	int				numlen;

	relen = 0;
	ft_memset(str, 0, 64);
	num = va_arg(*args, unsigned long);
	(num >= HUINT && flags->lenmod[0] < 106) ? (num = 0) : (num);
	numlen = count_num(num, 10);
	numlen = base_conv(num, str, 16, numlen);
	!num && !flags->ptox ? flags->altform = 0 : flags->altform;
	if (**format == 'X')
	{
		flags->pre = "0X";
		upper(str);
	}
	else
		(flags->pre) = "0x";
	flags->preper || flags->negwidth ? flags->zpad = 0 : flags->zpad;
	flags->preper && num == 0 ? print_padding_num(flags, 0, 0) :
		conv_x_write(flags, str, relen, numlen);
}
