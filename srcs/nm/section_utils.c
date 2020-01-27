/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:51:20 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/25 17:10:08 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	sectionLetter(t_sect *section) {
	if (!ft_strcmp(section->sectname, SECT_TEXT))
		return 'T';
	else if (!ft_strcmp(section->sectname, SECT_DATA))
		return 'D';
	else if (!ft_strcmp(section->sectname, SECT_BSS))
		return 'B';
	else
		return 'S';
}

char	getLetter(unsigned int type, unsigned int value, t_sect *section) {
	if (N_STAB & type) {
		return '-';
	} else if ((N_TYPE & type) == N_UNDF) {
		return  (value != 0) ? 'C' : 'U';
	} else if ((N_TYPE & type) == N_ABS) {
		return 'A';
	} else if ((N_TYPE & type) == N_INDR) {
		return 'I';
	} else if (section != NULL) {
		return sectionLetter(section);
	} else if ((type & N_TYPE) == N_PBUD)
		return 'U';
	return '?';
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
