/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:47:26 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 16:05:36 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_archive(t_ofile *ofile, int flags)
{
	t_ofile			*oar;
	struct ar_hdr	*hdr;

	if (!(oar = init()))
		return (1);
	oar->name = ofile->name;
	oar->size = ofile->size;
	hdr = (struct ar_hdr*)((void*)ofile->ptr + SARMAG);
	while (!is_overflow(hdr, oar->size))
	{
		hdr = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size);
		oar->ptr = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if ((oar->swap = is_32(oar->ptr)) != -1)
		{
			print_ar_name(ofile->name, hdr);
			handle_32(oar, flags);
		} else if ((oar->swap = is_64(oar->ptr)) != -1)
		{
			print_ar_name(ofile->name, hdr);
			handle_64(oar, flags);
		}
	}
	free(oar);
	return (0);
}
