/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:49:34 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 17:54:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_server.h"

void		usage_warning(char *str)
{
	if (str)
		ft_printf("Illegal option: %s\n");
	ft_printf("USAGE:\n\
./server -p <port> -x <width> -y <height> -n <team> [team] [team]\
... -c <nb> -t <t>\n\n-p port number\n-x world width\n-y world height\n\
-n team1 name ... team2 name ...\n\
-c number of clients authorized at the beginning of the game\n-t time unit\
divider (the greater t is, the faster the game will go)\n\n");
}
