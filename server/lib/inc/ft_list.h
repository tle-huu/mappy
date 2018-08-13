/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:59:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/17 16:50:22 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include "libft.h"

typedef struct		s_list
{
	void			*data;
	size_t			d_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_dblist
{
	void			*data;
	size_t			d_size;
	struct s_dblist	*prec;
	struct s_dblist	*next;
}					t_dblist;

typedef struct		s_queue
{
	t_dblist		*first;
	t_dblist		*last;
	int				qlen;
	int				min;
	int				max;
}					t_queue;

typedef struct		s_ffqueue
{
	t_list			*first;
	t_list			*last;
	int				qlen;
	int				min;
	int				max;
}					t_ffqueue;

/*
**	Doubly linked lists
*/

t_dblist			*ft_dblistnew(void *content, size_t content_size);
t_dblist			*ft_dblistpop(t_dblist *node);
void				ft_dblistinsert(t_dblist *current, t_dblist *insert);
t_dblist			*ft_dblistcritpop(t_dblist *node, int (*f)(void *));
t_dblist			*ft_dblmergesort(t_dblist *head, int (*f)(void *, void *));

/*
**	Queues, using doubly linked list
*/

t_dblist			*ft_popfirst(t_queue *key);
t_dblist			*ft_poplast(t_queue *key);
t_dblist			*ft_middel(t_queue *key, t_dblist *remove);
int					ft_enqueue(t_queue *key, void *data, size_t size);
int					ft_penqueue(t_queue *key, void *data, size_t size,
					int32_t (*f)(t_dblist *, t_dblist *));
void				ft_pushfirst(t_queue *key, t_dblist *data);
void				ft_pushlast(t_queue *key, t_dblist *data);
void				ft_queue_postmsort(t_queue *key);
void				ft_queuedel(t_queue *key, t_dblist *(*f)(t_dblist *del));

/*
**	List functions (stack)
*/

t_list				*ft_listpopfront(t_list **node);
t_list				*ft_listcritpop(t_list **node, int (*f)(void *));
t_list				*ft_sublistpop(t_list **node, int (*f)(void *));
void				ft_listadd(t_list **alst, void *content,
					size_t content_size);
t_list				*ft_listnew(void *content, size_t content_size);

#endif
