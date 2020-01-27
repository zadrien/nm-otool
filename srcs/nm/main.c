/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:12:28 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/18 14:35:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_flags	flags[8] = { { 'a', A }, { 'g', G },  { 'u', u },
							 { 'U', U }, {'p', P }, {'m', M}, {'n', n}, {'d', DEBUG} };
int     usage()
{
	ft_putstr_fd("nm ", 2);
	ft_putendl_fd("<executable>", 2);
	return (1);
}

int     main(int ac, char **av)
{
	(void)ac;
	int				i;
	int				ret;
	unsigned int	opt;

	opt = 0;
	if ((i = getFlags(av, &opt, flags, 8)) == 0)
		return 0;
	if (!av[i])
		return (mapFile("a.out", opt, nm));
	while (av[i])
		ret = mapFile(av[i++], opt, nm);
	return (ret);
}
