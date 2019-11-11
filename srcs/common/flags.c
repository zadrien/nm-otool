/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:03:01 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 20:26:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		getFlags(char **arg, unsigned int *opt, t_flags *arr, size_t len) {
	size_t	i;
	size_t	y;
	size_t	j;

	i = 0;
	j = 0;
	y = -1;
	while (arg[i++] != NULL) {
		if (arg[i][0] == '-' && arg[i][1] != '-') {
			while (arg[i][++j] != '\0') {
				while (++y < len) {
					if (arr[y].c == arg[i][j]) {
						*opt = *opt | arr[y].b;
						break ;
					}
				}
				if (y == len) {
					printf("[P] otool: option don't exist: %c\n", arg[i][j]);
					return 0;
				}
				y = -1;
			}
			j = 0;
		} else
			break ;
	}
	return i++;
}
