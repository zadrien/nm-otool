/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:05:08 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:15:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/* int		is_fat(void *ptr) { */
/* 	unsigned int magic; */

/* 	magic = *(unsigned int*)ptr; */
/* 	if (magic == FAT_CIGAM || magic == FAT_MAGIC) */
/* 		return 1; */
/* 	return 0; */
/* } */

void	handle_fat(void *ptr, int flags) {
	size_t				nstructs;
	size_t				i;
	int					swap;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	i = 0;
	swap = (*(unsigned int*)ptr) == FAT_CIGAM ? 1 : 0;
	hdr = (struct fat_header*)ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	nstructs = swap ? OSSwapInt32(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
		nm((void*)ptr + (swap ? OSSwapInt32(ar->offset) : ar->offset), flags);
}
