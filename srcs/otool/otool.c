/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 13:14:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	otool_32(t_ofile *ofile, int flags)
{
	int					i;
	int					ncmds;
	struct mach_header	*hdr;
	struct load_command	*lc;

	i = 0;
	hdr = (struct mach_header*)ofile->ptr;
	ncmds = ofile->swap ? swp_int(hdr->ncmds) : hdr->ncmds;
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header), ofile->swap);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			section_32(ofile, (void*)lc, flags);
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size)
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
}

void	otool_64(t_ofile *ofile, int flags)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*hdr;
	struct load_command		*lc;

	i = 0;
	hdr = (struct mach_header_64*)ofile->ptr;
	ncmds = ofile->swap ? swp_int(hdr->ncmds) : hdr->ncmds;
	lc = swap_load_cmd((void*)ofile->ptr + sizeof(struct mach_header_64), ofile->swap);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			section_64(ofile, (void*)lc, flags);
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size)
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
}

void	otool_ar(t_ofile *ofile, int flags)
{
	t_ofile			*oar;
	struct ar_hdr	*hdr;
	
	if (!(oar = init()))
		return ;
	oar->name = ofile->name;
	oar->size = ofile->size;
 	hdr = (struct ar_hdr*)((void*)ofile->ptr + SARMAG);
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
		}
	}
	free(oar);
}

void	otool_fat(t_ofile *ofile, int flags)
{
	int					nstructs;
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
		ofat->ptr = ofile->ptr + (ofile->swap ? swp_int(ar->offset) : ar->offset);
		ofat->size = ofile->size;
		if ((unsigned long)ofat->ptr < (unsigned long)ofat->size)
			otool(ofat, flags);
		free(ofat);
	}
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
		if ((ofile->swap = arr[i].check(ofile->ptr)) >= 0)
		{
			arr[i].f(ofile, flags);
			return (0);
		}
	ft_putstr_fd("otool: ", 2);
	ft_putstr_fd(ofile->name, 2);
	ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
	return (1);
}
