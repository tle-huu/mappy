/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:18:39 by nkouris           #+#    #+#             */
/*   Updated: 2018/07/13 11:47:06 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NUM_H
# define FT_NUM_H

# include "libft.h"

# define BASEKEY "0123456789abcdef"
# define ATOI(x) (x & 0xF)
# define ITOA(x) (x | 0x30)

int					ft_atoi(const char *str);
long				ft_atol(const char *str);
long				ft_natol(const char *str, size_t n);
int					ft_atoi_base(const char *str, int base);
long				ft_atol_base(const char *str, int base);
char				*ft_itoa(int n);
int					ft_numlen(int num);
char				*ft_itoa_base(int n, int base);
char				*ft_uitoa_base(unsigned int n, int base);
char				*ft_nuitoa_base(unsigned int n, int base, int length);

#endif
