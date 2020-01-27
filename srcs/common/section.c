/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:35:37 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/26 13:16:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_lst	*init_sectlst() {
	t_lst	*lst;
	if (!(lst = (t_lst*)malloc(sizeof(t_lst))))
		return NULL;
	lst->nbr = 0;
	lst->ptr = NULL;
	return lst;
	
}

void	freeSection(t_lst **lst) {

	if (*lst == NULL)
		return ;
	free((*lst)->ptr);
	free(*lst);
}
