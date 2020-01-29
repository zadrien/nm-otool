/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:37:01 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 17:44:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	pad(char *str)
{
	int			i;
	static int	sp = 7;

	i = sp - ft_strlen(str) - 1;
	while (i--)
		ft_putchar(' ');
	ft_putstr(str);
	ft_putchar(' ');
}

void	print_value(t_symbol *s)
{
	static int	i = 0;

	if (!i)
		i = ft_strlen(s->value);
	if (s->type == 'U')
		ft_putstr(i == 16 ? SPACE_64B : SPACE_32B);
	else
		ft_putstr(s->value);
}
