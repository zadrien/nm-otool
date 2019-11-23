/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 18:35:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	otool_32(void *ptr, int flags, int swap) {
	int					i;
	int					ncmds;
	struct mach_header	*hdr;
	struct load_command	*lc;

	i = 0;
	(void)swap;
	hdr = (struct mach_header*)ptr;
	ncmds = hdr->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SEGMENT)
			section_32(ptr, (void*)lc, flags);
		lc = (void*)lc + lc->cmdsize;
	}
	return;
}

void	otool_64(void *ptr, int flags, int swap) {
	(void)ptr;
	(void)flags;
	size_t						i;
	size_t						ncmds;
	struct mach_header_64	*hdr;
	struct load_command		 *lc;
	
	i = 0;
	(void)swap;
	hdr = (struct mach_header_64*)ptr;
	ncmds = hdr->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header_64);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SEGMENT_64)
			section_64(ptr, (void*)lc, flags);
		lc = (void*)lc + lc->cmdsize;
	}
}

void	otool_ar(void *ptr, int flags, int swap) {
	void			*h;
	struct ar_hdr	*hdr;

	(void)swap;
	hdr = (struct ar_hdr*)((void*)ptr + SARMAG);
	while (42) {
		hdr = (struct ar_hdr*)((void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size));
		if (ft_strlen(hdr->ar_name) == 0)
			break ;
		h = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if (is_32(h) || is_64(h))
			print_ar_name(NULL, hdr);
		start(h, flags);
	}
}

void	otool_fat(void *ptr, int flags, int swap) {
	int					i;
	int					nstructs;
	struct fat_header	*hdr;
	struct fat_arch		*ar;

	i = 0;
	(void)swap;
	hdr = (struct fat_header*)ptr;
	ar = (void*)hdr + sizeof(struct fat_header);
	nstructs = swap ? swp_int(hdr->nfat_arch) : hdr->nfat_arch;
	if (nstructs > 0)
		start((void*)ptr + (swap ? swp_int(ar->offset) : ar->offset), flags);
}

int		start(void *ptr, int flags) {
	int				i;
	int				swap;
	static t_type	arr[4] = { {is_32, otool_32}, {is_64, otool_64},
							   {is_archive, otool_ar}, {is_fat, otool_fat} };

	i = 0;
	if (ptr == NULL)
		return 0;
	while (i < 4) {
		if ((swap = arr[i].check(ptr)) >= 0) {
			arr[i].f(ptr, flags, swap);
			return 0;
		}
		i++;
	}
	return 1;
}

int		otool(char *file, int flags) {
	void	*ptr;
	ft_putendl(file);

	ptr = NULL;
	if (mapFile(file, flags, start)) {
		printf("otool: %s: file format not found\n", file);
	}
	return 0;
}
