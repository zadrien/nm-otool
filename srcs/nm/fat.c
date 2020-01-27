/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:05:08 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 16:08:01 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		fat(t_ofile *ofat, int flags)
{
	if ((ofat->swap = is_32(ofat->ptr)) != -1)
		handle_32(ofat, flags);
	else if ((ofat->swap = is_64(ofat->ptr)) != -1)
		handle_64(ofat, flags);
	else if (is_archive(ofat->ptr) != -1)
		handle_archive(ofat, flags);
	return (0);
}

int		handle_fat(t_ofile *ofile, int flags)
{
	size_t				nstructs;
	t_ofile				*ofat;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	hdr = (struct fat_header*)ofile->ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	if (is_overflow(ar, ofile->size))
		return (1);
	nstructs = ofile->swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
	{
		if (!(ofat = init()))
			return (1);
		ofat->name = ofile->name;
		ofat->ptr = (void*)ofile->ptr +
			(ofile->swap ? swp_int(ar->offset) : ar->offset);
		ofat->size = ofile->size;
		ofat->swap = 0;
		if (!is_overflow(ofat->ptr, ofile->size))
			fat(ofat, flags);
		free(ofat);
	}
	return (0);
}
