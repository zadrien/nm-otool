/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_ar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:40:30 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 19:16:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		singleton(int value)
{
	static int i = 0;

	if (value == 0)
		return (i);
	else if (value < 0)
		i = 0;
	else if (value > 0)
		i = 1;
	return (i);
}

int		archive(t_ofile *ar, struct ar_hdr *hdr, int flags)
{
	if ((ar->swap = is_32(ar->ptr)) != -1)
	{
		print_ar_name(ar->name, hdr);
		otool_32(ar, flags);
	}
	else if ((ar->swap = is_64(ar->ptr)) != -1)
	{
		print_ar_name(ar->name, hdr);
		otool_64(ar, flags);
	}
	else if ((ar->swap = is_fat(ar->ptr)) != -1)
	{
		print_ar_name(ar->name, hdr);
		otool_fat(ar, flags);
	}
	return (1);
}

int		otool_ar(t_ofile *ofile, int flags)
{
	t_ofile			*oar;
	struct ar_hdr	*hdr;

	if (!(oar = init()))
		return (1);
	oar->name = ofile->name;
	oar->size = ofile->size;
	hdr = (struct ar_hdr*)((void*)ofile->ptr + SARMAG);
	singleton(1);
	while ((unsigned long)hdr < (unsigned long)oar->size)
	{
		hdr = (struct ar_hdr*)((void*)hdr +
						sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size));
		oar->ptr = (void*)hdr +
					sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if (is_overflow(hdr, oar->size))
			break ;
		archive(oar, hdr, flags);
	}
	singleton(-1);
	free(oar);
	return (0);
}
