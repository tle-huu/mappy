/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 12:51:07 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/19 17:57:57 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# define BUFF_SIZE 512

typedef struct		s_line
{
	char			item[BUFF_SIZE + 1];
	int				len;
	int				pos;
	int				cont;
	int				links;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);

#endif
