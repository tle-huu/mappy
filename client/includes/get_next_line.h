/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:25:17 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/08/07 12:45:02 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

# define BUFF_SIZE 30720
# define SUCCESS 1
# define ERROR -1

typedef struct		s_list
{
	void			*content;
	long long int	content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_chunk
{
	int		fd;
	char	*str;
}					t_chunk;


int			get_next_line(const int fd, char **line);

#endif
