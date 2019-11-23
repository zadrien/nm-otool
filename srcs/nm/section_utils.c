/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:51:20 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/22 19:55:24 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_lst	*init_sectlst() {
	t_lst	*lst;
	if (!(lst = (t_lst*)malloc(sizeof(t_lst))))
		return NULL;
	lst->nbr = 0;
	lst->ptr = NULL;
	return lst;
	
}

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
