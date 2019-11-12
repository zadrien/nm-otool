/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/12 12:32:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	otool_32(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
	
	return;
}

void	otool_64(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
	size_t						i;
	size_t						ncmds;
	struct mach_header_64	*hdr;
	struct load_command		 *lc;
	
	i = 0;
	hdr = (struct mach_header_64*)ptr;
	ncmds = hdr->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header_64);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			ft_putendl("symtab");
		} else if (lc->cmd == LC_SEGMENT_64) {
//			ft_putendl("segment");
			parseSection_64(ptr, (void*)lc, flags);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void	otool_ar(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
}

void	otool_fat(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
}

int		start(void *ptr, int flags) {
	size_t			i;
	static t_type	arr[4] = { {is_32, otool_32}, {is_64, otool_64},
							   {is_archive, otool_ar}, {is_fat, otool_fat} };

	i = 0;
	if (ptr == NULL)
		return 0;
	while (i < 4) {
		if (arr[i].check(ptr)) {
			arr[i].f(ptr, flags);
			return 0;
		}
		i++;
	}
	printf("otool: %s: file format not found\n", "HMMMM!");
	return 0;
}

int		otool(char *file, int flags) {
	void	*ptr;
	ft_putendl(file);

	ptr = NULL;
	mapFile(file, flags, start);
	return 0;
}
