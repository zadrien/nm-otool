/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/25 12:52:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_header64(t_ofile *ofile) {
	struct mach_header_64 *header;

	header = swap_mh64(ofile->ptr, ofile->swap);
	printf("----- HEADER -----\n");
	printf("magic number: 0x%x\n", header->magic);
	printf("nbr of load commands: %d\n", header->ncmds);
	printf("size of all load commands: %d\n", header->sizeofcmds);
		
}

void	print_header(t_ofile *ofile) {
	struct mach_header *header;

	header = swap_mh(ofile->ptr, ofile->swap);
	printf("----- HEADER -----\n");
	printf("magic number: 0x%x\n", header->magic);
	printf("nbr of load commands: %d\n", header->ncmds);
	printf("size of all load commands: %d\n", header->sizeofcmds);
		
}

int		handle_64(t_ofile *ofile, int flags)
{
	uint32_t				i;
	t_lst					*lst;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	lst = NULL;
	if (DEBUG & flags)
		print_header64(ofile);
	header = swap_mh64(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header_64), ofile->swap);
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab_64(ofile, lc, lst, flags);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64) {
//			ft_putendl("segment found");
			if (saveSect64(ofile, &lst, (void*)lc) == NULL) {
//				ft_putendl("section failed");
				break ;
			}
		}
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size) {
//			ft_putendl("overflow");
			break ;
		}
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	freeSection(&lst);
	return (0);
}

int		handle_32(t_ofile *ofile, int flags)
{

	uint32_t			i;
	t_lst				*lst;
	struct mach_header	*header;
	struct load_command *lc;
	
	i = 0;
	lst = NULL;
	if (DEBUG & flags)
		print_header(ofile);
	header = swap_mh(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header), ofile->swap);
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab_32(ofile, lc, lst, flags);
			break ;
		} else if (lc->cmd == LC_SEGMENT)
			if (saveSect32(ofile, &lst, (void*)lc) == NULL)
				break ;
		if ((unsigned long)((void*)lc + lc->cmdsize) >= (unsigned long)ofile->size)
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	freeSection(&lst);
	return (0);
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
