/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:41:16 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 13:46:47 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		fileDontExist(char *file)
{
	ft_putstr_fd("nm: '", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd("': No such file", 2);
	return (0);
}

int		fileUnvalid(char *file, char *error)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	return (1);
}

int		validFile(struct stat buf)
{
	if (S_ISLNK(buf.st_mode) || S_ISREG(buf.st_mode))
		return (1);
	return (0);
}
