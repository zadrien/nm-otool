/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:35:37 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 17:45:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_lst	*init_sectlst(void)
{
	t_lst	*lst;

	if (!(lst = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	lst->nbr = 0;
	lst->ptr = NULL;
	return (lst);
}

void	free_section(t_lst **lst)
{
	t_lst	*tmp;

	if (!(*lst))
		return ;
	tmp = *lst;
	if (tmp->nbr > 0)
		free(tmp->ptr);
	free(tmp);
}
