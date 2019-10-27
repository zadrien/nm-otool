/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/27 12:21:38 by zadrien          ###   ########.fr       */
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
	struct mach_header_64	*header;
	struct load_command *lc;
	
	i = 0;
	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_64(ptr, lc, flags);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}


void	handle_32(void *ptr, int flags) {

	int					i;
	int					ncmds;
	struct mach_header	*header;
	struct load_command	*lc;

	i = 0;
	header = (struct mach_header*)ptr;
	printf("ncmds: %u\n", header->ncmds);
	ncmds = header->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_32(ptr, lc, flags);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
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
  } else {
	  ft_putendl_fd("unvalid file", 2);
  }
  return 0;
}
