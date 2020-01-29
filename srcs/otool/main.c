/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:14:00 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 16:32:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		usage(void)
{
	ft_putendl("that's not good");
	return (0);
}

int		otool(t_ofile *ofile, int flags)
{
	int				i;
	static t_type	arr[4] = {{is_32, otool_32}, {is_64, otool_64},
							{is_archive, otool_ar}, {is_fat, otool_fat}};

	i = -1;
	if (ofile == NULL)
		return (1);
	while (++i < 4)
		if ((ofile->swap = arr[i].check(ofile->ptr)) >= 0)
			return (arr[i].f(ofile, flags));
	ft_putstr_fd("otool: ", 2);
	ft_putstr_fd(ofile->name, 2);
	ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
	return (1);
}

int		main(int ac, char **av)
{
	int				i;
	int				ret;
	unsigned int	flags;
	static t_flags	array[2] = { {'t', T}, {'d', D}};

	i = 0;
	flags = 0;
	if (ac < 2)
		return (usage());
	if (!(i = get_flags(av, &flags, array, 2)))
		return (0);
	if (!av[i])
	{
		ft_putendl_fd("otool: at least one file must be specified.", 2);
		usage();
		return (0);
	}
	while (av[i])
		ret = map_file(av[i++], flags, otool);
	return (ret);
}
