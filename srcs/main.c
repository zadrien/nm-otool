/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/05 10:42:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int     usage(char *exe, char *usage)
{
    ft_putstr_fd(exe, 2)
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(usage, 2);
    return (1);
}

int     main(int ac, char **av)
{
    if (ac != 2)
        return (usage(av[0]));
    return (0);
}