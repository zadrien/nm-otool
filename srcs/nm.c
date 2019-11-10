/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 16:29:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	commands(void *ptr, int ncmds, int flags) {
  (void)flags;
  int			i;
  struct load_command	*lc;

  i = 0;
  lc = (struct load_command*)ptr;
  while (i < ncmds) {
    
    lc = (void*)ptr + lc->cmdsize;
    i++;
  }
}

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
//			break ; // ATTENTION
//			ft_putendl("symtab");
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
			symtab_64(ptr, lc, lst, flags);

		} else if (lc->cmd == LC_SEGMENT) {
			//saveSect42
		}
		lc = (void*)lc + lc->cmdsize;
	}
}





int	nm(void *ptr, int flags) {
  (void)flags;
  unsigned int mn;

  mn = *(unsigned int*)ptr;
//  printf("%u\n", nm);
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
