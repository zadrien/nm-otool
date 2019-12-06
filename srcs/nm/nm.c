/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/06 16:47:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_64(t_ofile *ofile, int flags)
{
	int						i;
	int						ncmds;
	t_lst					*lst;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	lst = NULL;
	header = (struct mach_header_64*)ofile->ptr;
	ncmds = ofile->swap ? swp_int(header->ncmds) : header->ncmds;
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header_64), ofile->swap);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB) {
			symtab_64(ofile->ptr, lc, lst, flags, ofile->swap);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			if (saveSect64(&lst, (void*)lc) == NULL) {
				printf("%i\n", i);
				ft_putendl("S");
				break ;
			}
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size) {
			ft_putendl("CMP");
			break ;
		}
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	ft_putendl("L");
	freeSection(&lst);
}

void	handle_32(t_ofile *ofile, int flags)
{

	int					i;
	int					ncmds;
	t_lst				*lst;
	struct mach_header	*header;
	struct load_command *lc;
	
	i = 0;
	lst = NULL;
	header = (struct mach_header*)ofile->ptr;
	ncmds = ofile->swap ? swp_int(header->ncmds) : header->ncmds;
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header), ofile->swap);
	while (i++ < ncmds) {
		if (lc->cmd == LC_SYMTAB) {
			symtab_32(ofile->ptr, lc, lst, flags, ofile->swap);
			break ;
		} else if (lc->cmd == LC_SEGMENT)
			if (saveSect32(&lst, (void*)lc, ofile->swap) == NULL)
				break ;
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size)
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	freeSection(&lst);
}

int	nm(t_ofile *ofile, int flags)
{
	size_t		i;
	static t_type arr[4] = {{is_32, handle_32}, {is_64, handle_64},
							{is_fat, handle_fat}, {is_archive, handle_archive}};

	i = -1;
	if (ofile == NULL)
		return (1);
	while (++i < 4)
		if ((ofile->swap = arr[i].check(ofile->ptr)) >= 0)
		{
			arr[i].f(ofile, flags);
			return (0);
		}
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(ofile->name, 2);
	ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
	return (1);
}
