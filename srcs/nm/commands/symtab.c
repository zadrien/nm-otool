/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 19:02:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		check_symbol(uint8_t type, int flags)
{
	if (N_STAB & type)
	{
		if (!(flags & A))
			return (1);
	}
	else if ((N_TYPE & type) == N_UNDF)
	{
		if (flags & U)
			return (1);
	}
	else if ((N_TYPE & type) == N_SECT)
	{
		if (flags & U_ONLY)
			return (1);
	}
	return (0);
}

void	symtab_64(t_ofile *ofile, struct symtab_command *symtab,
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
	while (++i < symtab->nsyms)
	{
		symbol[i] = swap_nlist64(symbol[i], ofile->swap);
		if (check_symbol(symbol[i].n_type, flags))
			continue ;
		if (!(el = new_symbol64(ofile, symbol[i], sects,
								offset + symbol[i].n_un.n_strx)))
			return ;
		new_elem(&lst, el, flags);
	}
	print_symbols(lst, flags);
	free_symbol(&lst);
}

void	symtab_32(t_ofile *ofile, struct symtab_command *symtab,
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
	while (++i < symtab->nsyms)
	{
		symbol[i] = swap_nlist(symbol[i], ofile->swap);
		if (check_symbol(symbol[i].n_type, flags))
			continue ;
		if (!(el = new_symbol(symbol[i], sects,
								offset + symbol[i].n_un.n_strx)))
			return ;
		new_elem(&lst, el, flags);
	}
	print_symbols(lst, flags);
	free_symbol(&lst);
}
