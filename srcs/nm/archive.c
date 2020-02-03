/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:47:26 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 11:03:25 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		archive(t_ofile *ofile, t_ofile *ar, struct ar_hdr *header, int flags)
{
	if ((ar->swap = is_32(ar->ptr)) != -1)
	{
		ft_putchar('\n');
		print_ar_name(ofile->name, header);
		handle_32(ar, flags);
	}
	else if ((ar->swap = is_64(ar->ptr)) != -1)
	{
		ft_putchar('\n');
		print_ar_name(ofile->name, header);
		handle_64(ar, flags);
	}
	return (0);
}

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
		oar->ptr = (void*)hdr
		+ sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if (is_overflow(hdr, oar->size))
			return (1);
		archive(ofile, oar, hdr, flags);
	}
	free(oar);
	return (0);
}
