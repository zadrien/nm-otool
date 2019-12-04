/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:48:35 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/29 17:19:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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

void	*addLst(t_symbol **lst, t_symbol *elem, int (*f)(t_symbol*, t_symbol*))
{
	int			i;
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
	int i;
	if (ft_strlen(e2->name) != 0)
		if ((i = ft_strcmp(e1->name, e2->name)) != 0)
			return i;
	if (e1->n_value != e2->n_value)
		return e1->n_value > e2->n_value;
	if (e2->type > 0)
		return e1->type < e2->type;
	if (e2->n_sect != 0)
		return e1->n_sect < e2->n_sect;
	return 1;
}

int		unSorted(t_symbol *e1, t_symbol *e2)
{
	(void)e1;	
	(void)e2;
	return -1;
}
