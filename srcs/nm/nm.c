/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:29:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	printHeader(void *ptr, int bit_32) {
	struct mach_header_64 *hdr;
	(void)bit_32;
	hdr = (struct mach_header_64*)ptr;
	printf("magic: %u\n", OSSwapInt32(hdr->magic));
	printf("filetype: %u\n", hdr->filetype);
	printf("sizeofcmds: %u\n", hdr->sizeofcmds);
	printf("ncmds: %u\n", OSSwapInt32(hdr->ncmds));
	printf("flags: %u\n", hdr->flags);
}

void	handle_64(void *ptr, int flags) {

	int						i;
	int						ncmds;
	t_lst					*lst;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	lst = NULL;
	header = (struct mach_header_64*)ptr;
	if (!header->cputype)
		return ;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB)
			symtab_64(ptr, lc, lst, flags);
		else if (lc->cmd == LC_SEGMENT_64)
			saveSect64(&lst, (void*)lc);
		lc = (void*)lc + lc->cmdsize;
	}
	freeSection(&lst);
}

void	handle_32(void *ptr, int flags) {

	int					i;
	int					ncmds;
	t_lst				*lst;
	struct mach_header	*header;
	struct load_command *lc;

	i = 0;
	lst = NULL;
	header = (struct mach_header*)ptr;
	if (!header->cputype)
		return ;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_32(ptr, lc, lst, flags);
		} else if (lc->cmd == LC_SEGMENT) {
			saveSect32(&lst, (void*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	freeSection(&lst);
}

int	nm(void *ptr, int flags) {
  (void)flags;
  size_t		i;
  static t_type arr[4] = {{is_32, handle_32}, {is_64, handle_64},
						  {is_fat, handle_fat}, {is_archive, handle_archive}};

  i = 0;
  while (i < 4) {
	  if (arr[i].check(ptr)) {
		  arr[i].f(ptr, flags);
		  return 0;
	  }
	  i++;
  }
  printf("otool: %s: file format not found\n", "HMM");
  return 0;
}
