/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:05:08 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/05 15:20:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	fat(t_ofile *ofat, int flags)
{
	ft_putendl("REEE");
	if ((ofat->swap = is_32(ofat->ptr)) != -1)
		handle_32(ofat, flags);
	else if ((ofat->swap = is_64(ofat->ptr)) != -1)
		handle_64(ofat, flags);
	else if (is_archive(ofat->ptr) != -1)
		handle_archive(ofat, flags);
}

void	handle_fat(t_ofile *ofile, int flags)
{
	size_t				nstructs;
	t_ofile				*ofat;
	struct fat_header	*hdr;
	struct fat_arch		*ar;
	
	hdr = (struct fat_header*)ofile->ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	if ((unsigned long)((void*)ar) >= (unsigned long)ofile->ptr)
		return ;
	nstructs = ofile->swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
	{
		if (!(ofat = init()))
			return ;
		ofat->name = ofile->name;
		ofat->ptr = (void*)ofile->ptr +
			(ofile->swap ? swp_int(ar->offset) : ar->offset);
		ofat->size = ofile->size;
		ofat->swap = 0;
		if ((unsigned long)ofat->ptr < (unsigned long)ofile->ptr)
			fat(ofat, flags);
		free(ofat);
	}
}
