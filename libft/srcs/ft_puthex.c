/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:50:24 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 15:56:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex(unsigned long long hex, int pad, int up)
{
	int		i;
	int		r;
	char	str[17];
	char	*s;

	i = 16;
	ft_bzero(str, 17);
	while (--i >= 0)
	{
		r = (int)(hex % (unsigned long long)16);
		hex = hex / (unsigned long long)16;
		if (r <= 15)
		{
			if (r < 10)
				str[i] = 48 + r;
			else
				str[i] = (up ? 65 : 97) + (r % 10);
		}
	}
	s = str + (16 - pad);
	ft_putstr(s);
}
