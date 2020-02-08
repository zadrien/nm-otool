/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:00:27 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/08 14:19:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		check_symbol(uint8_t type, int flags)
{
	if (N_STAB & type)
	{
		if (!(flags & A))
			return (1);
	}
	else if (((N_TYPE & type) == N_UNDF))
	{
		if ((flags & U_ONLY))
			return (1);
	}
	else if (((N_TYPE & type) == N_SECT))
	{
		if ((flags & U))
			return (1);
	}
	return (0);
}

t_symbol *init_symb(void) 
{
    t_symbol *new;

    if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
        return (NULL);
    new->next = NULL;
    new->value = NULL;
    new->sect = NULL;
    new->desc = NULL;
    new->stab = NULL;
    new->section = NULL;
    new->name = NULL;
    return (new);
}

void	free_symbol(t_symbol **symb)
{
	t_symbol *tmp;

	if (!(*symb))
		return ;
	tmp = *symb;
	if (tmp->type == '-')
	{
		tmp->sect != NULL ? free(tmp->sect) : 0;
		tmp->desc != NULL ? free(tmp->desc) : 0;
	}
    tmp->value != NULL ? free(tmp->value): 0;
    tmp->name != NULL ? free(tmp->name) : 0;
	free(tmp);
    *symb = NULL;
}

void	*free_symbol_lst(t_symbol **lst)
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
			free_symbol(&p);
		}
		lst = NULL;
	}
	return (NULL);
}

int     clear_lst(t_symbol **lst, int ret)
{
    free_symbol_lst(lst);
    return (ret);
}