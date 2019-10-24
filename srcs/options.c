/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:02 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/20 10:51:21 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

typedef struct		s_flags {
	char	c;
	unsigned int	b;
}					t_flags;


int options(char **arg, unsigned int *opt) {
	int				i;
	int				y;
	int				j;
	static t_flags	flags[3] = { { 'a', A }, { 'g', G },  { 'u', U } };

	(void)opt;
	i = 0;
	j = 0;
	y = -1;
	while (arg[++i] != NULL) {
		if (arg[i][0] == '-') {
			while (arg[i][++j] != '\0') {
				while (++y < 3) {
					if (flags[y].c == arg[i][j]) {
						(*opt) = *opt |  flags[y].b;
						break ;
					}
				}
				if (y == 3) {
					printf("nm: options don't exist: %c\n", arg[i][j]);
					return -1;
				}
				y = -1;
			}
			j = 0;
		} else
			break ;
	}

	return i++;
}
