/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:44:22 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/24 19:58:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_symbol *newSymbol64(t_ofile *ofile, struct nlist_64 symbol, t_lst *sections, char *name)
{
	t_symbol *new;

	new = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return NULL;
	new->n_type = symbol.n_type;
	new->n_desc = symbol.n_desc;
	new->n_sect = symbol.n_sect;
	new->n_value = symbol.n_value;
	new->value = ft_hex(symbol.n_value, 16);
	new->section = (N_TYPE & symbol.n_type) == N_SECT ? getSec(sections, symbol.n_sect): NULL;
	new->type = getLetter(symbol.n_type, symbol.n_value, new->section);
	if (new->type == '-') {
		new->stab = ft_type(symbol.n_type);
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strndup(name, (size_t)(ofile->size - (void*)name));
	new->next = NULL;
	return new;
}

t_symbol *newSymbol(t_ofile *ofile, struct nlist symbol, t_lst *sections, char *name)
{
	t_symbol *new;

	new = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return NULL;
	new->n_type = symbol.n_type;
	new->n_desc = symbol.n_desc;
	new->n_sect = symbol.n_sect;
	new->n_value = symbol.n_value;
	new->value = ft_hex(symbol.n_value, 8);
	new->section = (N_TYPE & symbol.n_type) == N_SECT ? getSec(sections, symbol.n_sect): NULL;
	new->type = getLetter(symbol.n_type, symbol.n_value, new->section);
	if (new->type == '-') {
		new->stab = ft_type(symbol.n_type);
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strdup(name);
//	new->name = ft_strndup(name, (size_t)(ofile->size - (void*)name));
	new->next = NULL;
	return new;
}

void	freeSymbol(t_symbol **lst)
{
	t_symbol	*tmp;
	t_symbol	*p;
	
	if (*lst == NULL)
		return ;
	tmp = *lst;
	while (tmp)
	{
		p = tmp;
		tmp = tmp->next;
		if (p->type == '-') {
			free(p->sect);
			free(p->desc);
		}
		free(p->name);
		free(p->value);
		if (p != *lst)
			free(p);
	}
	free(*lst);
	lst = NULL;
}
