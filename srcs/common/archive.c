/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:29:37 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 15:45:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	print_ar_name(char *path, struct ar_hdr *hdr)
{
	char	dst[17];

	ft_memset(dst, '\0', 17);
	if (!ft_strncmp(hdr->ar_name, AR_EFMT1, 3))
		ft_strcpy(dst, hdr->ar_fmag + 2);
	else
		ft_strncpy(dst, hdr->ar_name, 16);
	if (path)
		ft_putstr(path);
	ft_putstr("(");
	ft_putstr(dst);
	ft_putendl("):");
}
