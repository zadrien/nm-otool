/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:05:08 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/04 14:42:01 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_fat(void *ptr, int flags, int swap) {
	size_t				nstructs;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	hdr = (struct fat_header*)ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	nstructs = swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
		nm((void*)ptr + (swap ? swp_int(ar->offset) : ar->offset), flags);
}
