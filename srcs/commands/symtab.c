/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/27 11:58:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void byteValue(unsigned int v, int mask) {
	unsigned char bytes[4];

	bytes[0] = (v >> 24) & mask;
	bytes[1] = (v >> 16) & mask;
	bytes[2] = (v >> 8) & mask;
	bytes[3] = v  & mask;

	printf("%x%x%x ", (unsigned char)bytes[1], (unsigned char)bytes[2], (unsigned char)bytes[3]);
}


void	symtab_64(void *ptr, void *sc, int flags) {
	unsigned int			i;
	char					*strtable;
	struct symtab_command	*table;
	struct nlist_64			*nl;
	t_symbol				*s;
	t_symbol				*new;

	
	i = 0;
	s = NULL;
	table = (struct symtab_command*)sc;
	nl = (void*)ptr + table->symoff;
	strtable = (void*)ptr + table->stroff;
	while (i < table->nsyms) {
		new = NULL;
		if ((nl[i].n_type & N_STAB) && (flags & A)) {
				new = newStruct();
				new->stype = '-';
				new->symbol = ft_type(nl[i].n_type);
		} else if (!(nl[i].n_type & N_STAB)) {
			if (!(nl[i].n_sect == NO_SECT && flags & U)) {
				if (!(flags & u)) {
					new = newStruct();
					new->stype = symbol_type(nl[i].n_type, nl[i].n_sect);
				}
			}
		}

		if (new != NULL) {
			new->value = nl[i].n_value;
			new->n_type = nl[i].n_type;
			ft_strncpy(new->sect, ft_hex(nl[i].n_sect) + 14, 2); // OPT
			ft_strncpy(new->desc, ft_hex(nl[i].n_desc) + 12, 4); // OPT
			new->name = ft_strdup(strtable + nl[i].n_un.n_strx);
			
			add(&s, &new, cmpName);
		}
		i++;
	}

	print(s);
	return ;
}

void	symtab_32(void *ptr, void *sc, int flags) {
	unsigned int			i;
	char					*strtable;
	struct symtab_command	*table;
	struct nlist			*nl;
	t_symbol				*s;
	t_symbol				*new;

	
	i = 0;
	s = NULL;
	table = (struct symtab_command*)sc;
	nl = (void*)ptr + table->symoff;
	strtable = (void*)ptr + table->stroff;
	while (i < table->nsyms) {
		new = NULL;
		if ((nl[i].n_type & N_STAB) && (flags & A)) {
				new = newStruct();
				new->stype = '-';
				new->symbol = ft_type(nl[i].n_type);
		} else if (!(nl[i].n_type & N_STAB)) {
			if (!(nl[i].n_sect == NO_SECT && flags & U)) {
				if (!(flags & u)) {
					new = newStruct();
					new->stype = symbol_type(nl[i].n_type, nl[i].n_sect);
				}
			}
		}

		if (new != NULL) {
			new->value = nl[i].n_value;
			new->n_type = nl[i].n_type;
			ft_strncpy(new->sect, ft_hex(nl[i].n_sect) + 14, 2); // OPT
			ft_strncpy(new->desc, ft_hex(nl[i].n_desc) + 12, 4); // OPT
			new->name = ft_strdup(strtable + nl[i].n_un.n_strx);
			
			add(&s, &new, cmpName);
		}
		i++;
	}

	print(s);
	return ;
}
