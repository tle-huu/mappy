/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:30:25 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 16:46:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVENTORY_H
# define INVENTORY_H

# define FOOD(x) (x & 0xFF)
# define FOOD_INS(x, y) ((x & 0xFFFFFFFFFFFFFF00) | y)
# define LINEMATE(x) ((x >> 8) & 0xFF)
# define LINEMATE_INS(x, y) ((x & 0xFFFFFFFFFFFF00FF) | (y << 8))
# define SIBUR(x) ((x >> 16) & 0xFF)
# define SIBUR_INS(x, y) ((x & 0xFFFFFFFFFF00FFFF) | (y << 16))
# define DERAUMERE(x) ((x >> 24) & 0xFF)
# define DERAUMERE_INS(x, y) ((x & 0xFFFFFFFF00FFFFFF) | (y << 24))
# define MENDIANE(x) ((x >> 32) & 0xFF)
# define MENDIANE_INS(x, y) ((x & 0xFFFFFF00FFFFFFFF) | (y << 32))
# define PHIRAS(x) ((x >> 40) & 0xFF)
# define PHIRAS_INS(x, y) ((x & 0xFFFF00FFFFFFFFFF) | (y << 40))
# define THYSTAME(x) ((x >> 48) & 0xFF)
# define THYSTAME_INS(x, y) ((x & 0xFF00FFFFFFFFFFFF) | (y << 48))

typedef struct		s_inventory_plus
{
	void		(*food)(uint64_t *);
	void		(*line)(uint64_t *);
	void		(*sibu)(uint64_t *);
	void		(*dera)(uint64_t *);
	void		(*mend)(uint64_t *);
	void		(*phir)(uint64_t *);
	void		(*thys)(uint64_t *);
}					t_inventory_plus;

typedef struct			s_inventory_minus
{
	void			(*food)(uint64_t *);
	void			(*line)(uint64_t *);
	void			(*sibu)(uint64_t *);
	void			(*dera)(uint64_t *);
	void			(*mend)(uint64_t *);
	void			(*phir)(uint64_t *);
	void			(*thys)(uint64_t *);
}						t_inventory_minus;

typedef struct			s_inventory_methods
{
	t_inventory_plus	plus;
	t_inventory_minus	minus;
	void				(*add)(uint64_t *, int32_t);
	void				(*remove)(uint64_t *, int32_t);
}						t_inventory_methods;

t_inventory_methods		inventory;

#endif
