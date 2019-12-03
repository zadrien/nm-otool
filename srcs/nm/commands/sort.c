/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:48:35 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/03 21:03:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	*newElem(t_symbol **lst, t_symbol *el, int flags)
{
	unsigned int		i;
	static const t_sort	sort[1] = {{ P, unSorted }};

	i = 0;
	while (i < 1)
	{
		if (sort[i].flag & flags)
			return (addLst(lst, el, sort[i].f));
		i++;
	}
	return (addLst(lst, el, sortedByName));
}

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

int		unSorted(t_symbol *e1, t_symbol *e2)
{
	(void)e1;
	(void)e2;
	return (-1);
}
