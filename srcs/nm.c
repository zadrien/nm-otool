/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:41:02 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_64(void *ptr, int flags) {

	int i;
	int ncmds;
	t_lst					*lst;
	struct mach_header_64	*header;
	struct load_command *lc;

	i = 0;
	lst = NULL;
	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_64(ptr, lc, lst, flags);
		} else if (lc->cmd == LC_SEGMENT_64) {
			saveSect64(&lst, (void*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	freeSection(&lst);
}

void	handle_32(void *ptr, int flags) {

	int i;
	int ncmds;
	t_lst				*lst;
	struct mach_header	*header;
	struct load_command *lc;

	i = 0;
	lst = NULL;
	header = (struct mach_header*)ptr;
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
  unsigned int mn;

  mn = *(unsigned int*)ptr;
  if (mn == MH_CIGAM_64 || mn == MH_MAGIC_64) {
    handle_64(ptr, flags);
  } else if (mn == MH_CIGAM || mn == MH_MAGIC) {
    printf("32-bits architecture\n");
    if (mn == MH_CIGAM) {
      printf("should reverse\n");
    }
    handle_32(ptr, flags);
  } else if (is_archive(ptr)) {
	  handle_archive(ptr, flags);
  } else
	  ft_putendl_fd("unvalid file", 2);
  return 0;
}
