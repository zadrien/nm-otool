/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:05:08 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/04 17:42:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
void	fat(void *ptr, int flags, int swap)
{
	ft_putendl("REEE");
	if ((swap = is_32(ptr)) != -1)
		handle_32(ptr, flags, swap);
	else if ((swap = is_64(ptr)) != -1)
		handle_64(ptr, flags, swap);
	else if (is_archive(ptr) != -1)
		handle_archive(ptr, flags, swap);
}

void	handle_fat(void *ptr, int flags, int swap)
{
	size_t				nstructs;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	hdr = (struct fat_header*)ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	nstructs = swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	ft_putendl("???");
	if (nstructs > 0)
		fat((void*)ptr + (swap ? swp_int(ar->offset) : ar->offset), flags, swap);
}
