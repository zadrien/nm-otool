/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:05:08 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/07 17:21:26 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		fat(t_ofile *ofat, int flags)
{
	if ((ofat->swap = is_32(ofat->ptr)) != -1)
		return (handle_32(ofat, flags));
	else if ((ofat->swap = is_64(ofat->ptr)) != -1)
		return (handle_64(ofat, flags));
	else if (is_archive(ofat->ptr) != -1)
		return (handle_archive(ofat, flags));
	return (1);
}

t_ofile *new_fat(t_ofile *ofile, struct fat_arch *ar) {
	t_ofile *new;

	if(!(new = init()))
		return (NULL);
	new->name = ofile->name;
	new->ptr = (void*)ofile->ptr + (ofile->swap ? swp_int(ar->offset) : ar->offset);
	new->size = ofile->size;
	new->swap = 0;
	return (new);
}
int		handle_fat(t_ofile *ofile, int flags)
{
	int					ret;
	size_t				nstructs;
	t_ofile				*ofat;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	ret = 1;
	hdr = (struct fat_header*)ofile->ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	if (is_overflow(ar, ofile->size))
		return (1);
	nstructs = ofile->swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
	{
		if (!(ofat = new_fat(ofile, ar)))
			return (1);
		if (!is_overflow(ofat->ptr, ofile->size))
			ret = fat(ofat, flags);
		free(ofat);
	}
	return (ret);
}
