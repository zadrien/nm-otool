/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:48:35 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 16:22:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	*addLst(t_symbol **lst, t_symbol *elem, int (*f)(t_symbol*, t_symbol*))
{
	int			i;
	t_symbol	*prev;
	t_symbol	*tmp;
	t_symbol	*cmp;

	if (*lst == NULL)
		return (*lst = elem);
	if (elem == NULL)
		return (NULL);
	prev = NULL;
	cmp = elem;
	tmp = *lst;
	while (tmp)
	{
		if ((i = f(tmp, cmp)) > 0)
		{
			if (prev == NULL)
			{
				elem->next = tmp;
				*lst = elem;
			} else {
				elem->next = tmp;
				prev->next = elem;
			}
			return (elem);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = elem;
	elem->next = NULL;
	return (elem);
}

int		sortedByName(t_symbol *e1, t_symbol *e2)
{
	return (ft_strcmp(e1->name, e2->name));
}

int		sorted_num(t_symbol *e1, t_symbol *e2)
{
	return e1->n_value >= e2->n_value;
}

int		unSorted(t_symbol *e1, t_symbol *e2)
{
	(void)e1;
	(void)e2;
	return (-1);
}

void	*newElem(t_symbol **lst, t_symbol *el, int flags)
{
	unsigned int		i;
	static const t_sort	sort[2] = {{ P, unSorted }, {n, sorted_num} };

	i = -1;
	while (++i < 2)
		if (sort[i].flag & flags)
			return (addLst(lst, el, sort[i].f));
	return (addLst(lst, el, sortedByName));
}
