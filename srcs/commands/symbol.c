/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:44:22 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:49:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_symbol *newSymbol64(struct nlist_64 symbol, t_lst *sections, char *offset)
{
	t_symbol *new;

	new = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return NULL;
	new->value = ft_hex(symbol.n_value, 16);
	new->section = (N_TYPE & symbol.n_type) == N_SECT ? getSec(sections, symbol.n_sect): NULL;
	new->type = getLetter(symbol.n_type, new->section);
	if (new->type == '-') {
		new->stab = ft_type(symbol.n_type);
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strdup(offset + symbol.n_un.n_strx);
	new->next = NULL;
	return new;
}

t_symbol *newSymbol(struct nlist symbol, t_lst *sections, char *offset)
{
	t_symbol *new;

	new = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return NULL;
	new->value = ft_hex(symbol.n_value, 16);
	new->section = (N_TYPE & symbol.n_type) == N_SECT ? getSec(sections, symbol.n_sect): NULL;
	new->type = getLetter(symbol.n_type, new->section);
	if (new->type == '-') {
		new->stab = ft_type(symbol.n_type);
		new->sect = ft_hex(symbol.n_sect, 2);
		new->desc = ft_hex(symbol.n_desc, 4);
	}
	new->ext = symbol.n_type & N_EXT;
	new->name = ft_strdup(offset + symbol.n_un.n_strx);
	new->next = NULL;
	return new;
}

void	freeSymbol(t_symbol **lst) {
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
