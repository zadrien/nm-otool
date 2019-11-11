/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:14:00 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 20:26:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "otool.h"

static t_flags array[1] = {{ 't', T }};

int usage() {
	ft_putendl("that's not good");
	return 0;
}


/* int		getFlags(char **arg, unsigned int *opt, t_flags *arr, size_t len) { */
/* 	size_t	i; */
/* 	size_t	y; */
/* 	size_t	j; */

/* 	i = 0; */
/* 	j = 0; */
/* 	y = -1; */
/* 	while (arg[i++] != NULL) { */
/* 		if (arg[i][0] == '-' && arg[i][1] != '-') { */
/* 			while (arg[i][++j] != '\0') { */
/* 				while (++y < len) { */
/* 					if (arr[y].c == arg[i][j]) { */
/* 						*opt = *opt | arr[y].b; */
/* 						break ; */
/* 					} */
/* 				} */
/* 				if (y == len) { */
/* 					printf("[P] otool: option don't exist: %c\n", arg[i][j]); */
/* 					return 0; */
/* 				} */
/* 				y = -1; */
/* 			} */
/* 			j = 0; */
/* 		} else */
/* 			break ; */
/* 	} */
/* 	return i++; */
/* } */


int		main(int ac, char **av) {
	int				i;
	unsigned int	flags;

	i = 0;
	flags = 0;
	if (ac < 2)
b		return usage();

	if (!(i = getFlags(av, &flags, array, 1)))
		return 0;
	
	otool(av[i], flags);
	return 0;
}
