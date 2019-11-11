/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:40:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	symtab_64(void *ptr, void *lc, t_lst *sects, int flags) {
	unsigned int			i;
	char					*name;
	struct symtab_command	*symtab;
	struct nlist_64			*symbol;
	t_symbol					*lst;
	t_symbol					*el;
	
	i = -1;
	lst = NULL;
	symtab = (struct symtab_command*)lc;
	symbol = ptr + symtab->symoff;
	name = ptr + symtab->stroff;
	while (++i < symtab->nsyms) {
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

void	symtab_32(void *ptr, void *lc, t_lst *sects, int flags) {
	unsigned int			i;
	char					*name;
	struct symtab_command	*symtab;
	struct nlist			*symbol;
	t_symbol				*lst;
	t_symbol				*el;
	
	i = -1;
	lst = NULL;
	symtab = (struct symtab_command*)lc;
	symbol = ptr + symtab->symoff;
	name = ptr + symtab->stroff;
	while (++i < symtab->nsyms) {
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
	freeSymbol(&lst);
}

