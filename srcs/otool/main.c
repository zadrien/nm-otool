/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:14:00 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 15:05:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "otool.h"

static t_flags array[2] = { {'t', T}, {'d', d} };

int usage() {
	ft_putendl("that's not good");
	return 0;
}

int		main(int ac, char **av)
{
	int				i;
	int				ret;
	unsigned int	flags;

	i = 0;
	flags = 0;
	if (ac < 2)
		return usage();
	if (!(i = getFlags(av, &flags, array, 2)))
		return 0;
	if (!av[i])
	{
		ft_putendl_fd("otool: at least one file must be specified.", 2);
		usage();
		return (0);
	}
	while (av[i])
		ret = mapFile(av[i++], flags, otool);
	return (ret);
}
