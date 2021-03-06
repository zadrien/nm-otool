/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:30:39 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 17:27:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		check_lc64(t_ofile *ofile, struct load_command *lc, t_lst **lst,
																	int flags)
{
	void	*new;

	if (lc->cmd == LC_SEGMENT_64)
	{
		if ((new = sect_64(ofile, (void*)lc, flags)) != NULL)
			save_section(lst, lc, new);
	}
	return (1);
}

int		check_lc32(t_ofile *ofile, struct load_command *lc, t_lst **lst,
																	int flags)
{
	void	*new;

	if (lc->cmd == LC_SEGMENT)
	{
		if ((new = sect_32(ofile, (void*)lc, flags)) != NULL)
			save_section(lst, lc, new);
	}
	return (1);
}
