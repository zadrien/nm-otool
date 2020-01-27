/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 14:32:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

/* int		otool_32(t_ofile *ofile, int flags) */
/* { */
/* 	int					i; */
/* 	int					ncmds; */
/* 	struct mach_header	*hdr; */
/* 	struct load_command	*lc; */

/* 	i = 0; */
/* 	hdr = (struct mach_header*)ofile->ptr; */
/* 	ncmds = ofile->swap ? swp_int(hdr->ncmds) : hdr->ncmds; */
/* 	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header), ofile->swap); */
/* 	while (i++ < ncmds) */
/* 	{ */
/* 		if (lc->cmd == LC_SEGMENT) */
/* 			section_32(ofile, (void*)lc, flags); */
/* 		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size) */
/* 			break ; */
/* 		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap); */
/* 	} */
/* 	return (0); */
/* } */

int otool_64(t_ofile	*ofile, int flags) {
	int						ret;
	void					*new;
	t_lst					*lst;
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct segment_command_64	*sg;
	
	i = 0;
	ret = 1;
	lst = NULL;
	header = swap_mh64(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header_64), ofile->swap);
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64) {
			new = sect_64(ofile, (void*)lc, flags);
			if (new)
				save_section(ofile, &lst, new);
			new = NULL;
		}
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size) {
			ret = 0;
			break ;
		}
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	if (ret) 
		print_saved_section64(ofile, lst);
	freeSection(&lst);
	return (0);
}

int otool_32(t_ofile *ofile, int flags) {
	int					ret;
	void				*new;
	t_lst				*lst;
	uint32_t			i;
	struct mach_header	*header;
	struct load_command	*lc;
	struct segment_command	*sg;
	
	i = 0;
	ret = 1;
	lst = NULL;
	header = swap_mh(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header), ofile->swap);
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT) {
			new = sect_32(ofile, (void*)lc, flags);
			if (new)
				save_section(ofile, &lst, new);
			new = NULL;
		}
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size) {
			ret = 0;
			break ;
		}
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	if (ret) 
		print_saved_section32(ofile, lst);
	freeSection(&lst);
	return (0);
}

int		singleton(int value) {
	static int i = 0;
	
	if (value == 0)
		return i;
	else if (value < 0)
		i = 0;
	else if (value > 0)
		i = 1;
	return i;
}

int		fat(t_ofile *ofat, int flags) {
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
	if ((unsigned long)((void*)ar) >= (unsigned long)ofile->size)
		return (1);
	nstructs = ofile->swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
	{
		if (!(ofat = init()))
			return (1);
		ofat->name = ofile->name;
		ofat->ptr = ofile->ptr + (ofile->swap ? swp_int(ar->offset) : ar->offset);
		ofat->size = ofile->size; // WARINING
		if ((unsigned long)ofat->ptr < (unsigned long)ofat->size)
			fat(ofat, flags);
		free(ofat);
	}
	return (0);
}

int		otool_ar(t_ofile *ofile, int flags)
{
	t_ofile			*oar;
	struct ar_hdr	*hdr;
	
	if (!(oar = init()))
		return (1);
	oar->name = ofile->name;
	oar->size = ofile->size;
 	hdr = (struct ar_hdr*)((void*)ofile->ptr + SARMAG);
	singleton(1);
	while ((unsigned long)hdr < (unsigned long)oar->size)
	{
		hdr = (struct ar_hdr*)((void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size));
		oar->ptr = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if ((oar->swap = is_32(oar->ptr)) != -1)
		{
			print_ar_name(oar->name, hdr);
			otool_32(oar, flags);
		} else if((oar->swap = is_64(oar->ptr)) != -1)
		{
			print_ar_name(oar->name, hdr);
			otool_64(oar, flags);
		} else if ((oar->swap = is_fat(oar->ptr)) != -1) {
			print_ar_name(oar->name, hdr);
			otool_fat(oar, flags);
				
		}
				   
	}
	singleton(-1);
	free(oar);
	return (0);
}


int		otool(t_ofile *ofile, int flags)
{
	int				i;
	static t_type	arr[4] = { {is_32, otool_32}, {is_64, otool_64},
							   {is_archive, otool_ar}, {is_fat, otool_fat} };

	i = -1;
	if (ofile == NULL)
		return (1);
	while (++i < 4)
		if ((ofile->swap = arr[i].check(ofile->ptr)) >= 0) {
			return (arr[i].f(ofile, flags));
		}
	ft_putstr_fd("otool: ", 2);
	ft_putstr_fd(ofile->name, 2);
	ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
	return (1);
}
