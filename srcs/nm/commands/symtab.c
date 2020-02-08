/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/08 15:30:56 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		symtab_64(t_ofile *ofile, struct symtab_command *symtab,
												t_lst *sects, int flags)
{
	uint32_t				i;
	void					*offset;
	t_symbol				*lst;
	t_symbol				*el;
	struct nlist_64			*symbol;

	i = -1;
	lst = NULL;
	symtab = swap_symtab_cmd((void*)symtab, ofile->swap);
	offset = ofile->ptr + symtab->stroff;
	symbol = ofile->ptr + symtab->symoff;
	// if (is_overflow(symbol + symtab->strsize, ofile->size)) {
	// 	ft_putendl("OUT");
	// 	return (1);
	// }
	if (!is_overflow(symbol, ofile->size) && !is_overflow(offset, ofile->size))
		while (++i < symtab->nsyms)
		{
			symbol[i] = swap_nlist64(symbol[i], ofile->swap);
			if (!(el = verify_integrity64(ofile, symbol[i], sects, offset)))
				return (clear_lst(&lst, 1));
			if (check_symbol(symbol[i].n_type, flags))
				free_symbol(&el);
			el != NULL ? new_elem(&lst, el, flags) : 0;
		}
	return (print_symbols(&lst, flags));
}

int		symtab_32(t_ofile *ofile, struct symtab_command *symtab,
												t_lst *sects, int flags)
{
	uint32_t				i;
	char					*offset;
	t_symbol				*lst;
	t_symbol				*el;
	struct nlist			*symbol;

	i = -1;
	lst = NULL;
	symtab = swap_symtab_cmd((void*)symtab, ofile->swap);
	offset = ofile->ptr + symtab->stroff;
	symbol = ofile->ptr + symtab->symoff;
	if (is_overflow((ofile->ptr + symtab->stroff) + symtab->strsize, ofile->size))
		return (1);
	if (!is_overflow(symbol, ofile->size) && !is_overflow(offset, ofile->size))
		while (++i < symtab->nsyms)
		{
			symbol[i] = swap_nlist(symbol[i], ofile->swap);
			if (!(el = verify_integrity32(symbol[i], sects, offset)))
				return (clear_lst(&lst, 1));
			if (check_symbol(symbol[i].n_type, flags))
				free_symbol(&el);
			el != NULL ? new_elem(&lst, el, flags) : 0;
		}
	return (print_symbols(&lst, flags));
}
