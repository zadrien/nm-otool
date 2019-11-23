/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 18:30:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_64(void *ptr, int flags, int swap) {

	int						i;
	int						ncmds;
	t_lst					*lst;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	(void)swap;
	lst = NULL;
	header = (struct mach_header_64*)ptr;
	if (!header->cputype)
		return ;
	ncmds = swap ? swp_int(header->ncmds) : header->ncmds;
	lc = swap_load_cmd((void *)ptr + sizeof(struct mach_header_64), swap);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_64(ptr, lc, lst, flags, swap);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			if (saveSect64(&lst, (void*)lc) == NULL)
				break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, swap);
	}
	freeSection(&lst);
}

void	handle_32(void *ptr, int flags, int swap) {

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
	ncmds = swap ? swp_int(header->ncmds) : header->ncmds;
	lc = swap_load_cmd((void *)ptr + sizeof(struct mach_header), swap);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_32(ptr, lc, lst, flags, swap);
			break ;
		} else if (lc->cmd == LC_SEGMENT)
			if (saveSect32(&lst, (void*)lc, swap) == NULL)
				break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, swap);
	}
	freeSection(&lst);
}

int	nm(void *ptr, int flags) {
  (void)flags;
  size_t		i;
  int			swap;
  static t_type arr[4] = {{is_32, handle_32}, {is_64, handle_64},
						  {is_fat, handle_fat}, {is_archive, handle_archive}};

  i = 0;
  while (i < 4) {
	  if ((swap = arr[i].check(ptr)) >= 0) {
		  arr[i].f(ptr, flags, swap);
		  return 0;
	  }
	  i++;
  }
  printf("otool: %s: file format not found\n", "HMM");
  return 0;
}
