/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 08:44:22 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:32:36 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void print(t_symbol *el) {
	ft_putstr(el->type == 'U' ? "                ": el->value);
	ft_putchar(' ');
	if (el->type == '-')
		ft_putchar(el->type);
	else
		ft_putchar(el->ext ? el->type : el->type + 32);
	ft_putchar(' ');
	if (el->type == '-') {
		ft_putstr(el->sect);
		ft_putchar(' ');
		ft_putstr(el->desc);
		ft_putchar(' ');
		ft_putstr(el->stab);
		ft_putchar(' ');	
	}
	ft_putendl(el->name);
}

void printText(t_symbol *el) {
	t_sect *s;
	ft_putstr(el->type == 'U' ? "                " : el->value);
	if (el->section) {
		s = el->section ;
		ft_putstr(" (");
		ft_putstr(s->segname);
		ft_putchar(',');
		ft_putstr(s->sectname);
		ft_putstr(") ");
	} else {
		ft_putstr(el->type == 'U' ? " (undefined)" : " (?)");
	}
	ft_putchar(' ');
	ft_putstr(el->ext ? STR_EXT : STR_N_EXT);
	ft_putchar(' ');
	ft_putstr(el->name);
	ft_putendl(el->type == 'U' ? STR_LIBSYS : "");
	
}

void printSymbols(t_symbol *lst, int flags) {
	t_symbol	*tmp;
	
	if (!lst)
		return ;
	tmp = lst;
	while (tmp) {
		if (flags & M)
			printText(tmp);
		else
			print(tmp);
		tmp = tmp->next;
	}
}

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
		free(p->value); // OUI
		if (p != *lst)
			free(p);
	}
	free(*lst);
	lst = NULL;
}

void	*newElem(t_symbol **lst, t_symbol *el, int flags)
{
	unsigned int		i;
	static const t_sort	sort[1] = {{ P, unSorted }};

	i = 0;
	while (i < 1) {
		if (sort[i].flag & flags)
			return addLst(lst, el, sort[i].f);
		i++;
	}
	return addLst(lst, el, sortedByName);
}

/* void	*addLst(t_symbol **lst, t_symbol **elem, int (*f)(t_symbol*, t_symbol*)) */
/* { */
/* 	int i; */
/* 	t_symbol	*prev; */
/* 	t_symbol	*tmp; */
/* 	t_symbol	*cmp; */
	
/* 	if (*lst == NULL) { */
/* 		*lst = *elem; */
/* 		return *lst; */
/* 	} */

/* 	if (*elem == NULL) */
/* 		return NULL; */
	
/* 	prev = NULL; */
/* 	cmp = *elem; */
/* 	tmp = *lst; */
/* 	while (tmp) { */
/* 		if ((i = f(tmp, cmp)) > 0) { */
/* 			if (prev == NULL) { */
/* 				cmp->next = tmp; */
/* 				*lst = *elem; */
/* 			} else { */
/* 				(*elem)->next = tmp; */
/* 				prev->next = *elem; */
/* 			} */
/* 			return cmp; */
/* 		} */
/* 		prev = tmp; */
/* 		tmp = tmp->next; */
/* 	} */
/* 	prev->next = cmp; */
/* 	cmp->next = NULL; */
/* 	return cmp; */
/* } */

void	*addLst(t_symbol **lst, t_symbol *elem, int (*f)(t_symbol*, t_symbol*))
{
	int i;
	t_symbol	*prev;
	t_symbol	*tmp;
	t_symbol	*cmp;
	
	if (*lst == NULL) {
		*lst = elem;
		return *lst;
	}

	if (elem == NULL)
		return NULL;
	
	prev = NULL;
	cmp = elem;
	tmp = *lst;
	while (tmp) {
		if ((i = f(tmp, cmp)) > 0) {
			if (prev == NULL) {
				elem->next = tmp;
				*lst = elem;
			} else {
				elem->next = tmp;
				prev->next = elem;
			}
			return elem;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = elem;
	elem->next = NULL;
	return elem;
}


int		sortedByName(t_symbol *e1, t_symbol* e2)
{
	return ft_strcmp(e1->name, e2->name);
}

int		unSorted(t_symbol *e1, t_symbol *e2)
{
	(void)e1;	
	(void)e2;
	return -1;
}
