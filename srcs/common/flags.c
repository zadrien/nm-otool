/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:03:01 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 15:47:02 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		parse_flags(unsigned int *opt, char *str, t_flags *arr, size_t len)
{
	size_t	i;
	size_t	j;
	
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (++j < len)
			if (arr[j].c == str[i])
			{
				*opt = *opt | arr[j].b;
				break ;
			}
		if (j == len)
		{
			printf("%s: option don't exist: %c\n", "nm", str[i]);
			return (1);
		}
	}
	return (0);
}

int		get_flags(char **arg, unsigned int *opt, t_flags *arr, size_t len)
{
	size_t	i;

	i = 0;
	while (arg[++i])
	{
		if (!ft_strcmp(arg[i], "--"))
			return (i + 1);
		if (arg[i][0] == '-' && arg[i][1] != '-')
		{
			if (parse_flags(opt, arg[i] + 1, arr, len))
				return (0);
		} else
			break ;
	}
	return (i);
}
