/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:14:00 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/05 17:19:24 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "otool.h"

static t_flags array[1] = {{ 't', T }};

int usage() {
	ft_putendl("that's not good");
	return 0;
}



int		main(int ac, char **av) {
	int				i;
	unsigned int	flags;

	i = 0;
	flags = 0;
	if (ac < 2)
		return usage();
	if (!(i = getFlags(av, &flags, array, 1)))
		return 0;
	return (mapFile(av[i], flags, otool));
}
