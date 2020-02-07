/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:44:22 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/07 18:35:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void *free_new(t_symbol **new)
{
	free(*new);
	return (NULL);
}

t_symbol	*new_symbol64(t_ofile *ofile, struct nlist_64 symbol,
												t_lst *sections, char *name)
{
	t_symbol *new;

	new = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
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
//		printf("%u\n", symbol.n_type); // pprinnf
		if(!(new->stab = ft_type(symbol.n_type)))
			return free_new(&new);
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	if (is_overflow((void*)name, ofile->size))
		return NULL;
	new->name = ft_strndup(name, (size_t)(ofile->size - (void*)name));
	new->next = NULL;
	return (new);
}
t_symbol	*let_see(t_ofile *ofile, struct nlist_64 symbol, t_lst *sections, void *offset)
{
	t_symbol *new;
	if (!(new = new_symbol64(ofile, symbol, sections, offset + symbol.n_un.n_strx)))
		return (NULL);
	// if (check_symbol(symbol.n_type, flags))
	// {
	// 	free_section(&new);
	// }
	return (new);
}
t_symbol	*new_symbol(struct nlist symbol, t_lst *sections, char *name)
{
	t_symbol	*new;

	new = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return (NULL);
	new->next = NULL;
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
		if(!(new->stab = ft_type(symbol.n_type)))
			return free_symbol(&new);
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strdup(name);
	return (new);
}

void	*free_symbol(t_symbol **lst)
{
	t_symbol	*tmp;
	t_symbol	*p;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			p = tmp;
			tmp = tmp->next;
			if (p->type == '-')
			{
				free(p->sect);
				free(p->desc);
			}
			free(p->name);
			free(p->value);
			free(p);
		}
		lst = NULL;
	}
	return (NULL);
}
