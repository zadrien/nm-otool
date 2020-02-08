/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:44:22 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/08 15:30:43 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_symbol	*verify_integrity64(t_ofile *ofile, struct nlist_64 symbol,
												t_lst *sections, void *offset)
{
	t_symbol *new;
	if (!(new = new_symbol64(ofile, symbol, sections,
												offset + symbol.n_un.n_strx))) 
		return (NULL);
	return (new);
}

t_symbol	*verify_integrity32(struct nlist symbol,
												t_lst *sections, void *offset)
{
	t_symbol *new;
	if (!(new = new_symbol(symbol, sections,
												offset + symbol.n_un.n_strx)))
		return (NULL);
	return (new);
}

t_symbol	*new_symbol64(t_ofile *ofile, struct nlist_64 symbol,
												t_lst *sections, char *name)
{
	t_symbol *new;

	new = NULL;
	if (!(new = init_symb()))
		return (NULL);
	new->n_type = symbol.n_type;
	new->n_desc = symbol.n_desc;
	new->n_sect = symbol.n_sect;
	new->n_value = symbol.n_value;
	new->value = ft_hex(symbol.n_value, 16);
	new->section = (N_TYPE & symbol.n_type) == N_SECT ?
		get_section(sections, symbol.n_sect) : NULL;
	new->type = get_type(symbol.n_type, symbol.n_value, new->section);
	if (new->type == '-')
	{
		ft_putchar(new->type);
		//printf(" %hhu\n", symbol.n_type);
		if(!(new->stab = ft_type(symbol.n_type))) {
			ft_putendl("no stab");
			free_symbol(&new);
			return (NULL);
		}
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	if (is_overflow(ofile->ptr + (ofile->size - (void*)name), ofile->size))
		return (NULL);
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strndup(name, (size_t)(ofile->size - (void*)name));
	return (new);
}

t_symbol	*new_symbol(struct nlist symbol, t_lst *sections, char *name)
{
	t_symbol	*new;

	new = NULL;
	if (!(new = init_symb()))
		return (NULL);
	new->n_type = symbol.n_type;
	new->n_desc = symbol.n_desc;
	new->n_sect = symbol.n_sect;
	new->n_value = symbol.n_value;
	new->value = ft_hex(symbol.n_value, 8);
	new->section = (N_TYPE & symbol.n_type) == N_SECT ?
		get_section(sections, symbol.n_sect) : NULL;
	new->type = get_type(symbol.n_type, symbol.n_value, new->section);
	if (new->type == '-')
	{
		if(!(new->stab = ft_type(symbol.n_type))) {
			free_symbol(&new);
			return NULL;
		}
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strdup(name);
	return (new);
}