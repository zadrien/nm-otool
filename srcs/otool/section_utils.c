/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:33:02 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 16:10:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

t_lst	*save_section(t_lst **lst, struct load_command *lc, void *saved)
{
	t_section		*page;

	if (*lst == NULL)
		if (!(*lst = init_sectlst()))
			return (NULL);
	if (!saved)
		return (*lst);
	if ((*lst)->nbr == 0)
	{
		if (!(page = (t_section*)malloc(sizeof(t_section) * ((*lst)->nbr + 1))))
			return (NULL);
		page->segment = lc;
		page->ptr = saved;
		(*lst)->ptr = page;
		(*lst)->nbr++;
	}
	else
	{
		if (!(page = (t_section*)malloc(sizeof(t_section) * ((*lst)->nbr + 1))))
			return (NULL);
		(*lst)->nbr++;
		copy_section(lst, &page, saved, lc);
	}
	return (*lst);
}

t_lst	*copy_section(t_lst **lst, t_section **new, void *saved, void *lc)
{
	uint32_t	i;
	t_lst		*tmp;
	t_section	*tmp_sect;

	i = 0;
	tmp = *lst;
	ft_memcpy(*new, tmp->ptr, (sizeof(t_section) * tmp->nbr));
	free(tmp->ptr);
	tmp->ptr = *new;
	tmp_sect = (void*)*new + sizeof(t_section) * tmp->nbr;
	tmp_sect->segment = lc;
	tmp_sect->ptr = saved;
	return (*lst);
}
