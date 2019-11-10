/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:14:34 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/06 17:23:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strndup(char *str, size_t len)
{
    size_t  i;
    char    *line;

    line = NULL;
    if (str)
    {
        i = 0;
        if (!(line = (char*)malloc(sizeof(char) * (len + 1))))
            return (NULL);
        while (i < len)
        {
            line[i] = str[i];
            i++;
        }
        line[i] = '\0';
    }
    return (line);
}
