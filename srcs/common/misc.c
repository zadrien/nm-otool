/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:41:16 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 15:57:31 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		file_dontexist(char *file)
{
	ft_putstr_fd("nm: '", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd("': No such file", 2);
	return (0);
}

int		file_unvalid(char *file, char *error)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}

int		valid_file(struct stat buf)
{
	if (S_ISLNK(buf.st_mode) || S_ISREG(buf.st_mode))
		return (1);
	return (0);
}

int		is_overflow(void *addr, void *limit)
{
	if ((unsigned long)addr >= (unsigned long)limit)
		return (1);
	return (0);
}

uint64_t				swp_int(uint64_t v)
{
	return (((v >> 24) & 0xff) | ((v << 8) & 0xff0000) |
			((v >> 8) & 0xff00) | ((v << 24) & 0xff000000));
}
