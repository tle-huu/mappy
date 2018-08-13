/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:47:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/13 12:17:40 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		d_list(t_line **line)
{
	t_line *next;

	while (*line)
	{
		next = (*line)->next;
		free(*line);
		*line = 0;
		*line = next;
	}
	return (0);
}

int		make_line(t_line *work, char **line)
{
	int		total;
	int		i;
	t_line	*head;

	total = 0;
	head = work;
	while (work)
	{
		total = total + work->len;
		work = work->next;
	}
	work = head;
	if (!(*line = (char *)ft_memalloc((sizeof(char) * total) + 1)))
		return (0);
	i = 0;
	while (work)
	{
		work->cont = 0;
		while (work->item[work->cont])
			(*line)[i++] = work->item[work->cont++];
		work = work->next;
	}
	d_list(&head);
	(*line)[i] = '\0';
	return (1);
}

void	work_check(t_line *work, t_line *left, char *buf)
{
	int i;
	int pos;
	int links;

	i = 0;
	pos = work->pos;
	while (i < work->cont && buf[i] != '\n')
		work->item[pos++] = buf[i++];
	work->len = pos;
	links = work->links + 1;
	work->len ? work->links = links : work->links;
	i++;
	while (i < work->cont)
		left->item[left->len++] = buf[i++];
	left->len ? (left->cont = 0) : (left->cont++);
	if (i == work->cont && buf[(i - 1)] == '\n')
		left->cont = 0;
	(work->next)->links = links;
	!left->cont ? d_list(&(work->next)) : i;
	!left->cont ? work->next = 0 : work->next;
}

int		left_check(t_line *work, t_line **left)
{
	int	i;

	i = 0;
	if (!(*left))
		!((*left) = (t_line *)ft_memalloc(sizeof(t_line))) ?
		((*left)->cont = -1) : ((*left)->cont++);
	while ((*left)->item[(*left)->pos] != '\n' && (*left)->len--)
		work->item[i++] = (*left)->item[(*left)->pos++];
	work->pos = i;
	work->len = i;
	if (((*left)->len + 1) == 1 || !((*left)->len + 1))
	{
		((*left)->item[(*left)->pos] == '\n') ?
		((*left)->cont = 0) : ((*left)->cont++);
		ft_bzero((*left)->item, BUFF_SIZE + 1);
		(*left)->pos = 0;
		(*left)->len = 0;
	}
	else
	{
		(*left)->pos++;
		(*left)->len--;
	}
	return ((*left)->cont);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE];
	t_line			*work;
	t_line			*head;
	static t_line	*left;

	if (fd < 0 || !(work = (t_line *)ft_memalloc(sizeof(t_line))) ||
		(left_check(work, &left) < 0))
		return (-1);
	head = work;
	while (left->cont)
	{
		if (!(work->next = (t_line *)ft_memalloc(sizeof(t_line)))
			|| (work->cont = read(fd, buf, (BUFF_SIZE - work->len))) < 0)
			return (-1);
		work_check(work, left, buf);
		if (!work->cont)
		{
			d_list(&left);
			return (work->links > 0 ? make_line(head, line) : d_list(&work));
		}
		work = work->next;
	}
	if (!(make_line(head, line)))
		return (-1);
	return (1);
}
