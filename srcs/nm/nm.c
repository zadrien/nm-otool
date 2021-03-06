/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 09:59:33 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/08 14:06:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		check_lc64(t_ofile *ofile, struct load_command *lc,
													t_lst **lst, int flags)
{
	if (lc->cmd == LC_SYMTAB)
	{
		if (symtab_64(ofile, (void*)lc, *lst, flags)) {
			ft_putendl("K");
			return (1);
		}
	}
	else if (lc->cmd == LC_SEGMENT_64)
	{
		if (!save_sect64(ofile, lst, (void*)lc))
			return (-1);
	}
	return (0);
}

int		handle_64(t_ofile *ofile, int flags)
{
	int						ret;
	uint32_t				i;
	t_lst					*lst;
	struct load_command		*lc;
	struct mach_header_64	*header;

	i = 0;
	ret = 0;
	lst = NULL;
	header = swap_mh64(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header_64), ofile->swap);
	while (i++ < header->ncmds)
	{
		if ((ret = check_lc64(ofile, lc, &lst, flags)) == 1)
			break ;
		if ((ret = is_overflow((void*)lc + lc->cmdsize, ofile->size)))
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	free_section(&lst);
	return (ret);
}

int		check_lc32(t_ofile *ofile, struct load_command *lc,
													t_lst **lst, int flags)
{
	if (lc->cmd == LC_SYMTAB)
	{
		symtab_32(ofile, (void*)lc, *lst, flags);
		return (1);
	}
	else if (lc->cmd == LC_SEGMENT)
	{
		if (!save_sect32(ofile, lst, (void*)lc))
			return (1);
	}
	return (0);
}

int		handle_32(t_ofile *ofile, int flags)
{
	int					ret;
	uint32_t			i;
	t_lst				*lst;
	struct mach_header	*header;
	struct load_command *lc;

	i = 0;
	ret = 0;
	lst = NULL;
	header = swap_mh(ofile->ptr, ofile->swap);
	lc = swap_load_cmd(ofile->ptr + sizeof(struct mach_header), ofile->swap);
	while (i++ < header->ncmds)
	{
		if (check_lc32(ofile, lc, &lst, flags))
			break ;
		if ((ret = is_overflow((void*)lc + lc->cmdsize, ofile->size)))
			break ;
		lc = swap_load_cmd((void*)lc + lc->cmdsize, ofile->swap);
	}
	free_section(&lst);
	return (ret);
}

int		nm(t_ofile *ofile, int flags)
{
	size_t			i;
	static t_type	arr[4] = {{is_32, handle_32}, {is_64, handle_64},
							{is_fat, handle_fat}, {is_archive, handle_archive}};

	i = -1;
	if (ofile == NULL)
		return (1);
	while (++i < 4)
		if ((ofile->swap = arr[i].check(ofile->ptr)) >= 0)
			return (arr[i].f(ofile, flags));
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(ofile->name, 2);
	ft_putendl_fd(": The file was not recognized as a valid object file.", 2);
	return (1);
}
