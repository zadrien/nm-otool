/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:46:03 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/06 16:51:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_lst	*saveSect64(t_lst **lst, void *ptr) {
	size_t						i;
	t_lst						*l;
	t_sect						*tmp;
	t_sect						*new;
	struct section_64			*sect;
	struct segment_command_64	*sg;

	i = 0;
	if (*lst == NULL)
		if (!(*lst = init_sectlst()))
			return NULL;
	sg = (struct segment_command_64*)ptr;
	if (sg->nsects == 0)
		return *lst;
	l = *lst;
	if (!(new = (t_sect*)malloc(sizeof(t_sect) * (l->nbr + sg->nsects))))
		return NULL;
	ft_memcpy(new, l->ptr, (sizeof(t_sect) * l->nbr));
	free(l->ptr);
	l->ptr = new;
	tmp = (void*)new + (sizeof(t_sect) * l->nbr);
	sect = (void*)ptr + sizeof(struct segment_command_64);
	while(i++ < sg->nsects) {
		ft_putendl(sect->sectname);
		if (!ft_strlen(sect->sectname)) {
			ft_putendl("ici");
			return NULL;
		}
		tmp->segname = sect->segname;
		tmp->sectname = sect->sectname;
		tmp = (void*)tmp + sizeof(t_sect);
		sect = (void*)sect + sizeof(struct section_64);
	}
	(*lst)->nbr += sg->nsects;
	return *lst;
}

t_lst	*saveSect32(t_lst **lst, void *ptr, int swap) {
	size_t					i;
	t_lst					*l;
	t_sect					*tmp;
	t_sect					*new;
	struct section			*sect;
	struct segment_command	*sg;

	i = 0;
	if (*lst == NULL)
		if (!(*lst = init_sectlst()))
			return NULL;
	l = *lst;
	sg = (struct segment_command*)ptr;
	sg->nsects = swap ? swp_int(sg->nsects) : sg->nsects;
	if (sg->nsects == 0)
		return *lst;
	if (!(new = (t_sect*)malloc(sizeof(t_sect) * (l->nbr + sg->nsects))))
		return NULL;
	ft_memcpy(new, l->ptr, (sizeof(t_sect) * l->nbr));
	free(l->ptr);
	l->ptr = new;
	tmp = (void*)new + (sizeof(t_sect) * l->nbr);
	sect = (void*)ptr + sizeof(struct segment_command);
	while(i++ < sg->nsects) {
		tmp->segname = sect->segname;
		tmp->sectname = sect->sectname;
		tmp = (void*)tmp + sizeof(t_sect);
		sect = (void*)sect + sizeof(struct section);
	}
	(*lst)->nbr += sg->nsects;
	return *lst;
}

void printSec(t_lst *lst) {
	int		i;
	t_lst	*tmp;
	t_sect	*sect;
	
	if (!lst)
		return ;
	tmp = lst;
	i = tmp->nbr;
	sect = tmp->ptr;
	while (--i) {
		printf("(%s, %s)\n", sect->segname, sect->sectname);
		sect = (void*)sect + sizeof(t_sect);
	}
}
