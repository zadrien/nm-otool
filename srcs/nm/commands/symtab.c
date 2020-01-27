/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/24 20:04:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_symtab(struct symtab_command *symtab) {
	printf("------ SYMTAB ------\n");
	printf("number of symbol table entries: %d\n", symtab->nsyms);
	printf("string table offset: %d - (%x)\n", symtab->stroff, symtab->stroff);
	printf("string table size in bytes: %d\n", symtab->strsize);
}

void	print_nlist64(struct nlist_64 nlist, t_symbol *symbol, char *offset) {
	(void)symbol;
	printf("\t ------ SYMBOL ------\n");
	printf("\t index string table: %d, %x\n", nlist.n_un.n_strx, nlist.n_un.n_strx);
	printf("\t name: %s\n", offset + nlist.n_un.n_strx);
	
}

void	print_nlist(struct nlist nlist, t_symbol *symbol, char *offset) {
	(void)symbol;
	printf("\t ------ SYMBOL ------\n");
	printf("\t index string table: %d, %x\n", nlist.n_un.n_strx, nlist.n_un.n_strx);
	printf("\t name: %s\n", offset + nlist.n_un.n_strx);
	
}


void print_symbol(struct nlist_64 symb) {
	printf("\t ------ SYMBOL ------\n");
	printf("\t index string table: %d\n", symb.n_un.n_strx);
	printf("\t type flag: %d\n", symb.n_type);
	printf("\t section number: %d\n", symb.n_sect);
	printf("\t description number: %d\n", symb.n_desc);
	printf("\t value of this symbol: %llu\n", symb.n_value);
}

void print_symbol32(struct nlist symb) {
	printf("\t ------ SYMBOL ------\n");
	printf("\t index string table: %d\n", symb.n_un.n_strx);
	printf("\t type flag: %d\n", symb.n_type);
	printf("\t section number: %d\n", symb.n_sect);
	printf("\t description number: %d\n", symb.n_desc);
	printf("\t value of this symbol: %u\n", symb.n_value);
}

void	saved_symbol(t_symbol *el) {
	printf("\t\t------ SAVED SYMBOL ------\n");
	printf("\t\tname: %s\n", el->name);
}

void	ft_putnendl(char *str, size_t length) {
	size_t	i;

	i = 0;
	while (i < length && str[i])
		ft_putchar(str[i++]);
	ft_putendl("");
}

void symtab_64(t_ofile *ofile, struct load_command *lc, t_lst *sects, int flags) {
	uint32_t						i;
	void					*offset;
	t_symbol				*lst;
	t_symbol				*el;
	struct nlist_64			*symbol;
	struct symtab_command	*symtab;

	i = -1;
	lst = NULL;
	symtab = swap_symtab_cmd((void*)lc, ofile->swap);
	offset = ofile->ptr + symtab->stroff;
	symbol = ofile->ptr + symtab->symoff;
	if (DEBUG & flags)
		print_symtab(symtab);
	while (++i < symtab->nsyms) {
		if (DEBUG & flags)
			print_symbol(symbol[i]);
		symbol[i] = swap_nlist64(symbol[i], ofile->swap);
		if (N_STAB & symbol[i].n_type) {
			if (!(flags & A))
				continue ;
		} else if ((N_TYPE & symbol[i].n_type) == N_UNDF) {
			if (flags & U)
				continue ;
		} else if ((N_TYPE & symbol[i].n_type) == N_SECT) {
			if (flags & u)
				continue ;
		}
		if (!(el = newSymbol64(ofile, symbol[i], sects, offset + symbol[i].n_un.n_strx)))
			return ;
		newElem(&lst, el, flags);
	}
	printSymbols(lst, flags);
	freeSymbol(&lst);
}

void	symtab_32(t_ofile *ofile, struct load_command *lc, t_lst *sects, int flags)
{
	uint32_t				i;
	char					*offset;
	t_symbol				*lst;
	t_symbol				*el;	
	struct nlist			*symbol;
	struct symtab_command	*symtab;
	

	i = -1;
	lst = NULL;
	symtab = swap_symtab_cmd((void*)lc, ofile->swap);
	offset = ofile->ptr + symtab->stroff;
	symbol = ofile->ptr + symtab->symoff;
	if (DEBUG & flags)
		print_symtab(symtab);
	while (++i < symtab->nsyms) {
		if (DEBUG & flags)
			print_symbol32(symbol[i]);
		symbol[i] = swap_nlist(symbol[i], ofile->swap);
		if (N_STAB & symbol[i].n_type) {
			if (!(flags & A))
				continue ;
		} else if ((N_TYPE & symbol[i].n_type) == N_UNDF) {
			if (flags & U)
				continue ;
		} else if ((N_TYPE & symbol[i].n_type) == N_SECT) {
			if (flags & u)
				continue ;
		}
		if (!(el = newSymbol(ofile, symbol[i], sects, offset + symbol[i].n_un.n_strx)))
			return ;
		if (DEBUG & flags)
			saved_symbol(el);
		newElem(&lst, el, flags);
	}
	printSymbols(lst, flags);
	freeSymbol(&lst);
}

