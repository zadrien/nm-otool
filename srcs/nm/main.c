/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:12:28 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 16:34:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		usage(void)
{
	ft_putstr_fd("nm ", 2);
	ft_putendl_fd("<executable>", 2);
	return (1);
}

void	print_file(char *file)
{
	ft_putstr(file);
	ft_putendl(":");
}

int		main(int ac, char **av)
{
	int				i;
	int				ret;
	int				print_name;
	unsigned int	opt;
	static t_flags	flags[8] = {{'a', A}, {'g', G}, {'u', U_ONLY}, {'U', U},
									{'p', P}, {'m', M}, {'n', N}};

	i = 0;
	opt = 0;
	print_name = 0;
	if ((i = get_flags(av, &opt, flags, 7)) == 0)
		return (0);
	if (!av[i])
		return (map_file("a.out", opt, nm));
	if (i < ac - 1)
		print_name = 1;
	while (av[i])
	{
		if (print_name)
			print_file(av[i]);
		ret = map_file(av[i++], opt, nm);
	}
	return (ret);
}
