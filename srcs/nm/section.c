/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:46:03 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:43:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	getLetter(unsigned int type, t_sect *section) {
	if (N_STAB & type) {
		return '-';
	} else if ((N_TYPE & type) == N_UNDF) {
		return  (type & N_EXT) ? 'U' : 'C';
	} else if ((N_TYPE & type) == N_ABS) {
		return 'A';
	} else if ((N_TYPE & type) == N_INDR) {
		return 'I';
	} else if (section != NULL) {
		if (!ft_strcmp(section->sectname, SECT_TEXT))
			return 'T';
		if (!ft_strcmp(section->sectname, SECT_DATA))
			return 'D';
		if (!ft_strcmp(section->sectname, SECT_CONST))
			return 'S';
		if (!ft_strcmp(section->sectname, SECT_BSS))
			return 'B';
	}
	return '?';
}

void	freeSection(t_lst **lst) {

	if (*lst == NULL)
		return ;
	free((*lst)->ptr);
	free(*lst);
}

void	*getSec(t_lst *lst, size_t nbr) {
	size_t		i;
	t_sect		 *sect;
	i = 1;
	if (lst == NULL)
		return NULL;
	if (nbr == 0)
		return NULL;
	if (nbr > lst->nbr)
		return NULL;
	sect = lst->ptr;
	while (i != nbr) {
		sect = (void*)sect + sizeof(t_sect);
		i++;
	}
	return sect;
}

t_lst	*saveSect64(t_lst **lst, void *ptr) {
	size_t						i;
	t_lst						*l;
	t_sect						*tmp;
	t_sect						*new;
	struct segment_command_64	*sg;
	struct section_64			*sect;

	i = 0;
	sg = (struct segment_command_64*)ptr;
	if (sg->nsects == 0)
		return *lst;
	if (*lst == NULL) {
		if (!(*lst = (t_lst*)malloc(sizeof(t_list))))
			return NULL;
		(*lst)->nbr = 0;
		(*lst)->ptr = NULL;
	}
	l = *lst;
	if (!(new = (t_sect*)malloc(sizeof(t_sect) * (l->nbr + sg->nsects))))
		return NULL;
	ft_memcpy(new, l->ptr, (sizeof(t_sect) * l->nbr));
	free(l->ptr);
	l->ptr = new;
	tmp = (void*)new + (sizeof(t_sect) * l->nbr);
	sect = (void*)ptr + sizeof(struct segment_command_64);
	while(i++ < sg->nsects) {
		tmp->segname = sect->segname;
		tmp->sectname = sect->sectname;
		tmp = (void*)tmp + sizeof(t_sect);
		sect = (void*)sect + sizeof(struct section_64);
	}
	(*lst)->nbr += sg->nsects;
	return *lst;
}

t_lst	*saveSect32(t_lst **lst, void *ptr) {
	size_t						i;
	t_lst						*l;
	t_sect						*tmp;
	t_sect						*new;
	struct segment_command		*sg;
	struct section				*sect;

	i = 0;
	sg = (struct segment_command*)ptr;
	if (sg->nsects == 0)
		return *lst;
	if (*lst == NULL) {
		if (!(*lst = (t_lst*)malloc(sizeof(t_list))))
			return NULL;
		(*lst)->nbr = 0;
		(*lst)->ptr = NULL;
	}
	l = *lst;
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
