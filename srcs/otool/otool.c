/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 19:25:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		fat(t_ofile *ofat, int flags)
{
	if ((ofat->swap = is_32(ofat->ptr)) != -1)
		otool_32(ofat, flags);
	else if ((ofat->swap = is_64(ofat->ptr)) != -1)
		otool_64(ofat, flags);
	else if (is_archive(ofat->ptr) != -1)
		otool_ar(ofat, flags);
	return (0);
}

int		otool_fat(t_ofile *ofile, int flags)
{
	int					nstructs;
	t_ofile				*ofat;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	hdr = (struct fat_header*)ofile->ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	if (is_overflow((void*)ar, ofile->size))
		return (1);
	nstructs = ofile->swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
	{
		if (!(ofat = init()))
			return (1);
		ofat->name = ofile->name;
		ofat->ptr = ofile->ptr +
					(ofile->swap ? swp_int(ar->offset) : ar->offset);
		ofat->size = ofile->size;
		if (!is_overflow(ofat->ptr, ofat->size))
			fat(ofat, flags);
		free(ofat);
	}
	return (0);
}

int		otool_64(t_ofile *ofile, int flags)
{
	int							ret;
	t_lst						*lst;
	uint32_t					i;
	struct mach_header_64		*header;
	struct load_command			*lc;

	i = 0;
	ret = 1;
	lst = NULL;
	header = swap_mh64(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr +
						sizeof(struct mach_header_64), ofile->swap);
	while (i++ < header->ncmds)
	{
		check_lc64(ofile, lc, &lst, flags);
		if ((ret = is_overflow((void*)lc + lc->cmdsize, ofile->size)))
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	if (!ret)
		print_saved_section64(ofile, lst);
	free_section(&lst);
	return (0);
}

int		otool_32(t_ofile *ofile, int flags)
{
	int						ret;
	t_lst					*lst;
	uint32_t				i;
	struct mach_header		*header;
	struct load_command		*lc;

	i = 0;
	ret = 1;
	lst = NULL;
	header = swap_mh(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr +
						sizeof(struct mach_header), ofile->swap);
	while (i++ < header->ncmds)
	{
		check_lc32(ofile, (void*)lc, &lst, flags);
		if ((ret = is_overflow((void*)lc + lc->cmdsize, ofile->size)))
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	if (!ret)
		print_saved_section32(ofile, lst);
	free_section(&lst);
	return (0);
}
