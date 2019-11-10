/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:47:26 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:44:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int is_archive(void *ptr) {
	if (ptr != NULL)
		if (!ft_strncmp((char*)ptr, ARMAG, SARMAG))
			return 1;
	return 0;
}

void	handle_archive(void *ptr, int flags)
{
	void			*h;
	char			dst[16];
	struct ar_hdr	*hdr;
	
	hdr = (struct ar_hdr*)((void*)ptr + SARMAG);
	while (42) {
		hdr = (struct ar_hdr*)((void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size));
		if (ft_strlen(hdr->ar_name) == 0)
			break ;
		ft_putendl("");
		ft_strcpy(dst, hdr->ar_fmag + 2);
		ft_putstr(dst);
		ft_putendl(":");
		h = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		handle_64(h, flags);
		ft_memset(dst, '\0', 16);
	}
}
