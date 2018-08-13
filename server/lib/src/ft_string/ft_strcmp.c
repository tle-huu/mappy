/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 14:31:35 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/10 11:23:47 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	c_s1;
	unsigned char	c_s2;

	i = 0;
	while (s1[i] || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			c_s1 = (unsigned char)s1[i];
			c_s2 = (unsigned char)s2[i];
			return (c_s1 - c_s2);
		}
	}
	return (0);
}
