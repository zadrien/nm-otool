/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 18:30:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	symtab_64(void *ptr, void *lc, t_lst *sects, int flags, int swap) {
	unsigned int			i;
	char					*name;
	struct symtab_command	*symtab;
	struct nlist_64			*symbol;
	t_symbol					*lst;
	t_symbol					*el;
	
	i = -1;
	lst = NULL;
	symtab = swap_symtab_cmd(lc, swap);
	symbol = ptr + symtab->symoff;
	name = ptr + symtab->stroff;
	while (++i < symtab->nsyms) {
		symbol[i] = swap_nlist64(symbol[i], swap);
		if (N_STAB & symbol[i].n_type) {
			if (!(flags & A))
				continue ;
		} else if ((N_TYPE & symbol[i].n_type) == N_UNDF) {
			if (flags & U)
				continue;
		} else if ((N_TYPE & symbol[i].n_type) == N_SECT) {
			if (flags & u)
				continue;
		}
		if (!(el = newSymbol64(symbol[i], sects, name)))
			return ;
		newElem(&lst, el, flags);
	}
	printSymbols(lst, flags);
	freeSymbol(&lst);
}

void	symtab_32(void *ptr, void *lc, t_lst *sects, int flags, int swap) {
	unsigned int			i;
	char					*name;
	struct symtab_command	*symtab;
	struct nlist			*symbol;
	t_symbol				*lst;
	t_symbol				*el;
	
	i = -1;
	lst = NULL;
	symtab = swap_symtab_cmd(lc, swap);
	symbol = ptr + symtab->symoff;
	name = ptr + symtab->stroff;
	while (++i < symtab->nsyms) {
		symbol[i] = swap_nlist(symbol[i], swap);
		if (N_STAB & symbol[i].n_type) {
			if (!(flags & A))
				continue ;
		} else if ((N_TYPE & symbol[i].n_type) == N_UNDF) {
			if (flags & U)
				continue;
		} else if ((N_TYPE & symbol[i].n_type) == N_SECT) {
			if (flags & u)
				continue;
		}
		if (!(el = newSymbol(symbol[i], sects, name)))
			return ;
		newElem(&lst, el, flags);
	}
	printSymbols(lst, flags);
//	ft_putendl("after printing symbol");
	freeSymbol(&lst);
}

