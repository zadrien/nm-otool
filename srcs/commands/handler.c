/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:34:58 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/27 11:31:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


void	format(t_symbol *el) { // to modify to a proper function without printf()

	if (el->stype == '-') {
		printf("%s %c %s %s %7s %s\n", ft_hex(el->value), el->stype, el->sect, el->desc, el->symbol, el->name);
	} else {
		printf("%16s %c %s\n", (el->stype == 'T' ? ft_hex(el->value) : ""), el->stype, el->name);
	}
}

void	print(t_symbol *lst) {
	t_symbol	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp) {
		format(tmp);
		tmp = tmp->next;
	}
}

char	symbol_type(unsigned int value, unsigned int sect) {

	if (sect == NO_SECT)
		return 'U';
	if (!(value ^ N_ABS)) {
		return 'A';
	} else if (!(value ^ N_SECT)) {
		return 'S';
	} else if (!(value ^ N_PBUD)) {
		return 'B';
	} else if (!(value ^ N_INDR)) {
		return 'I';
	} else {
		return 'T';
	}
}

t_symbol	*newStruct() {
	t_symbol	*s;

	if (!(s = (t_symbol*)malloc(sizeof(t_symbol))))
		return NULL;
	
	s->value = 0;
	s->n_type = 0;
	s->symbol = NULL;
	s->name = NULL;
	s->stype = '\0';
	s->next = NULL;
	return s;
}

void		freeStruct(t_symbol *node) {
	free(node->name);
	free(node);
}

void	*add(t_symbol **lst, t_symbol **elem, int (*f)(t_symbol*, t_symbol*)) {
	t_symbol	*prev;
	t_symbol	*tmp;
	t_symbol	*cmp;
	
	if (*lst == NULL) {
		*lst = *elem;
		return *lst;
	}

	if (*elem == NULL)
		return NULL;
	
	prev = NULL;
	cmp = *elem;
	tmp = *lst;
	while (tmp) {
		if (f(tmp, cmp) > 0) {
			if (prev == NULL) {
				cmp->next = tmp;
				*lst = *elem;
			} else {
				(*elem)->next = tmp;
				prev->next = *elem;
			}
			return cmp;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = cmp;
	cmp->next = NULL;
	return cmp;
}



/* sorted */
int		cmpName(t_symbol *e1, t_symbol* e2) {
	return ft_strcmp(e1->name, e2->name);
}


/* symbol-table order */
int		noOrdered(t_symbol *e1, t_symbol *e2) {
	(void)e1;	
	(void)e2;
	return 0;
}
