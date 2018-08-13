/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:14:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/19 18:33:47 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <wchar.h>
# include "libft.h"

# define BASE_FLAGS "0123456789abcdef"
# define HUINT 4294967296
# define MINLONG_SAFE 9223372036854775808U

typedef struct		s_flags
{
	unsigned int	altform : 1;
	unsigned int	zpad : 1;
	unsigned int	negwidth : 1;
	unsigned int	spacepad : 1;
	unsigned int	preper : 1;
	unsigned int	sign : 1;
	unsigned int	printsign : 1;
	unsigned int	ptox : 1;
	unsigned int	dolla : 1;
	unsigned int	capl : 1;
	unsigned int	apos : 1;
	int				fieldwidth;
	int				precision;
	int				n;
	int				nloops;
	char			lenmod[2];
	char			*pre;
	char			*str;
	int				strx;
	int				stri;
	int				wc;
	unsigned int	failure : 1;
}					t_flags;

/*
** Dispatcher
*/

int					ft_printf(const char *format, ...);

/*
** Store Flags
*/

void				store_pre(const char **format, t_flags *flags,
					va_list *args);

/*
** Print Flags
*/

int					print_padding(t_flags *flags, int *strlen);
int					print_padding_num(t_flags *flags, int relen, long lnum);

/*
** Conversion Flags diou
*/

void				conv_d_i(const char **format, t_flags *flags,
					va_list *args);
void				conv_u(const char **format, t_flags *flags, va_list *args);
void				conv_o(const char **format, t_flags *flags, va_list *args);

/*
** Conversion Flags sc
*/

void				conv_s(const char **format, t_flags *flags, va_list *args);
void				conv_c(t_flags *flags, va_list *args);
void				conv_flag(t_flags *flags);

/*
** Conversion Flags xp
*/

void				conv_c(t_flags *flags, va_list *args);
void				conv_p(t_flags *flags, va_list *args);
void				conv_x(const char **format, t_flags *flags, va_list *args);

/*
** Ulitobase
*/

int					count_num_signed(long long n, long base);
int					count_num(unsigned long n, unsigned long base);
int					base_conv_signed(long long n, char *address, long base,
					int len);
int					base_conv(unsigned long n, char *address,
					unsigned long base, int len);

/*
** Misc
*/

void				buf_store(t_flags *flags, int n, const char *store,
								unsigned char pad);
void				upper(char *str);
void				conv_n(t_flags *flags, va_list *args);
int					kill_switch(t_flags *flags);

#endif
