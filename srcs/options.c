/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:02 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/31 14:56:49 by zadrien          ###   ########.fr       */
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
	static t_flags	flags[6] = { { 'a', A }, { 'g', G },  { 'u', u }, { 'U', U }, {'p', P }, {'m', M}};

	(void)opt;
	i = 0;
	j = 0;
	y = -1;
	while (arg[++i] != NULL) {
		if (arg[i][0] == '-') {
			while (arg[i][++j] != '\0') {
				while (++y < 6) {
					if (flags[y].c == arg[i][j]) {
						(*opt) = *opt |  flags[y].b;
						break ;
					}
				}
				if (y == 6) {
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
