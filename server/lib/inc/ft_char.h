/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:46:23 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/20 13:45:27 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHAR_H
# define FT_CHAR_H

# include "libft.h"

# define TO_UPPER(x) (x ^ 0x20)
# define TO_LOWER(x) (x | 0x20)
# define IS_DIGIT(x) (x >= 48 && x <= 57)
# define IS_PRINT(x) (x >= 32 && x<= 126)
# define IS_ALPHA(x) ((x >= 65 && x <= 90) || (x >= 97 && x <= 122))
# define IS_ALNUM(x) (IS_DIGIT(x) || IS_ALPHA(x))
# define IS_WHSPC(x) (x == 32 || x == 10 || x == 11 || x == 13 || x == 12)
# define IS_ASCII(x) (x >= 0 && x <= 127)

#endif
