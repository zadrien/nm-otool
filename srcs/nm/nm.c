/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/04 18:32:40 by zadrien          ###   ########.fr       */
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
		ft_putnbr(i);ft_putendl(";;");
		if (lc->cmd == LC_SYMTAB) {
			symtab_64(ptr, lc, lst, flags, swap);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			if (saveSect64(&lst, (void*)lc) == NULL)
				break ;
		if ((void*)lc + lc->cmdsize)
			lc = swap_load_cmd((void*)lc + lc->cmdsize, swap);
		ft_putendl("W");
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
//	ft_putnbr(ncmds);
//	ft_putendl("??");
	while (i++ < ncmds) {
//		ft_putnbr(i);
//		ft_putendl("");
		if (lc->cmd == LC_SYMTAB) {
			symtab_32(ptr, lc, lst, flags, swap);
			break ;
		} else if (lc->cmd == LC_SEGMENT)
			if (saveSect32(&lst, (void*)lc, swap) == NULL)
				break ;
//		ft_putendl("l2");
		lc = swap_load_cmd((void*)lc + lc->cmdsize, swap);
//		ft_putendl("l3");
	}
//	ft_putendl("3");
	freeSection(&lst);
}

int	nm(char *name, void *ptr, int flags) {
  (void)flags;
  size_t		i;
  int			swap;
  static t_type arr[4] = {{is_32, handle_32}, {is_64, handle_64},
						  {is_fat, handle_fat}, {is_archive, handle_archive}};

  i = 0;
  if (ptr == NULL)
	  return (1);
  while (i < 4)
  {
	  if ((swap = arr[i].check(ptr)) >= 0)
	  {
		  arr[i].f(ptr, flags, swap);
		  return (0);
	  }
	  i++;
  }
  ft_putstr_fd("nm: ", 2);
  ft_putstr_fd(name, 2);
  ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
  return (1);
}

int	ofile_nm(t_ofile *ofile, int flags) {
  size_t		i;
  int			swap;
  static t_type arr[4] = {{is_32, handle_32}, {is_64, handle_64},
						  {is_fat, handle_fat}, {is_archive, handle_archive}};

  i = 0;
  if (ptr == NULL)
	  return (1);
  while (i < 4)
  {
	  if ((ofile->swap = arr[i].check(ofile->ptr)) >= 0)
	  {
		  arr[i].f(ptr, flags, swap);
		  return (0);
	  }
	  i++;
  }
  ft_putstr_fd("nm: ", 2);
  ft_putstr_fd(ofile->name, 2);
  ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
  return (1);
}
