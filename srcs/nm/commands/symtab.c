/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/07 18:33:03 by zadrien          ###   ########.fr       */
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
	else if (((N_TYPE & type) == N_UNDF))
	{
		if ((flags & U_ONLY))
			return (1);
	}
	else if (((N_TYPE & type) == N_SECT))
	{
		if ((flags & U))
			return (1);
	}
	return (0);
}

// int		lst_constructor(t_ofile *ofile, struct symtab_command *symtab, int flags)
// {
// 	t_symbol				*lst;
// 	t_symbol				*el;

// }

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
	printf("stroff: %u | strsize: %u\n", symtab->stroff, symtab->strsize);
	if (!is_overflow(symbol, ofile->size) && !is_overflow(offset, ofile->size))
		while (++i < symtab->nsyms)
		{
			symbol[i] = swap_nlist64(symbol[i], ofile->swap);
			// ft_putendl("?");
			// check_symbol(symbol[i].n_type, flags) ? (continue ): 0;
			// if (check_symbol(symbol[i].n_type, flags))
			// 	continue;
			// if (!(el = new_symbol64(ofile, symbol[i], sects,
			// 							offset + symbol[i].n_un.n_strx)))
			// 		return (1);
			if (!(el = let_see(ofile, symbol[i], sects, offset)))
				return (1);
			if (check_symbol(symbol[i].n_type, flags))
				free_symbol(&el);
			new_elem(&lst, el, flags);
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
	printf("stroff: %u | strsize: %u\n", symtab->stroff, symtab->strsize);
	if (!is_overflow(symbol, ofile->size) && !is_overflow(offset, ofile->size))
		while (++i < symtab->nsyms)
		{
			symbol[i] = swap_nlist(symbol[i], ofile->swap);

			if (check_symbol(symbol[i].n_type, flags))
				continue ;
			if (!(el = new_symbol(symbol[i], sects,
									offset + symbol[i].n_un.n_strx)))
				return (1);
			
			new_elem(&lst, el, flags);
			
		}
	return (print_symbols(&lst, flags));
}
