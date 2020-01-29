/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:46:03 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 16:14:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_lst	*copy_section64(t_lst **lst, t_sect **new, void *ptr,
						struct segment_command_64 *sg)
{
	size_t				i;
	t_lst				*l;
	t_sect				*tmp;
	struct section_64	*sect;

	i = 0;
	l = *lst;
	ft_memcpy(*new, l->ptr, (sizeof(t_sect) * l->nbr));
	free(l->ptr);
	l->ptr = *new;
	tmp = (void*)*new + (sizeof(t_sect) * l->nbr);
	sect = (void*)ptr + sizeof(struct segment_command_64);
	while (i++ < sg->nsects)
	{
		if (!ft_strlen(sect->sectname))
			return (NULL);
		tmp->segname = sect->segname;
		tmp->sectname = sect->sectname;
		tmp = (void*)tmp + sizeof(t_sect);
		sect = (void*)sect + sizeof(struct section_64);
	}
	(*lst)->nbr += sg->nsects;
	return (*lst);
}

t_lst	*copy_section(t_lst **lst, t_sect **new, void *ptr,
					struct segment_command *sg)
{
	uint32_t		i;
	t_lst			*l;
	t_sect			*tmp;
	struct section	*sect;

	i = 0;
	l = *lst;
	ft_memcpy(*new, l->ptr, (sizeof(t_sect) * l->nbr));
	free(l->ptr);
	l->ptr = *new;
	tmp = (void*)*new + (sizeof(t_sect) * l->nbr);
	sect = (void*)ptr + sizeof(struct segment_command);
	while (i++ < sg->nsects)
	{
		if (!ft_strlen(sect->sectname))
			return (NULL);
		tmp->segname = sect->segname;
		tmp->sectname = sect->sectname;
		tmp = (void*)tmp + sizeof(t_sect);
		sect = (void*)sect + sizeof(struct section);
	}
	(*lst)->nbr += sg->nsects;
	return (*lst);
}

t_lst	*save_sect64(t_ofile *ofile, t_lst **lst, void *ptr)
{
	t_sect						*new;
	struct segment_command_64	*sg;

	if (*lst == NULL)
		if (!(*lst = init_sectlst()))
			return (NULL);
	sg = swap_sg_cmd64(ptr, ofile->swap);
	if (sg->nsects == 0)
		return (*lst);
	if (!(new = (t_sect*)malloc(sizeof(t_sect) * ((*lst)->nbr + sg->nsects))))
		return (NULL);
	if (copy_section64(lst, &new, ptr, sg) == NULL)
	{
		display_error(ofile->name,
					"The file was not recognized as a valid object file.");
		return (NULL);
	}
	return (*lst);
}

t_lst	*save_sect32(t_ofile *ofile, t_lst **lst, void *lc)
{
	t_sect					*new;
	struct segment_command	*sg;

	if (*lst == NULL)
		if (!(*lst = init_sectlst()))
			return (NULL);
	sg = swap_sg_cmd(lc, ofile->swap);
	if (sg->nsects == 0)
		return (*lst);
	if (!(new = (t_sect*)malloc(sizeof(t_sect) * ((*lst)->nbr + sg->nsects))))
		return (NULL);
	if (copy_section(lst, &new, lc, sg) == NULL)
	{
		display_error(ofile->name,
					"The file was not recognized as a valid object file.");
		return (NULL);
	}
	return (*lst);
}
