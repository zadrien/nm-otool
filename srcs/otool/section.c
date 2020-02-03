/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:34 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 15:48:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	*sect_64(t_ofile *ofile, struct segment_command_64 *sg, int flags)
{
	uint32_t					i;
	struct section_64			*sect;

	i = 0;
	sg = swap_sg_cmd64(sg, ofile->swap);
	sect = swap_sect64((void*)sg + sizeof(struct segment_command_64),
																ofile->swap);
	if (!is_overflow((void*)sect, ofile->size))
		while (i++ < sg->nsects)
		{
			if (!ft_strlen(sect->sectname))
				continue ;
			if (!ft_strcmp(sect->segname, SEG_TEXT) &&
									!ft_strcmp(sect->sectname, SECT_TEXT))
				if (flags & T)
					return (swap_sect64(sect, ofile->swap));
			if (!ft_strcmp(sect->segname, SEG_DATA) &&
									!ft_strcmp(sect->sectname, SECT_DATA))
				if (flags & D)
					return (swap_sect64(sect, ofile->swap));
			sect = (void*)sect + sizeof(struct section_64);
			if (is_overflow((void*)sect, ofile->size))
				return (NULL);
		}
	return (NULL);
}

void	*sect_32(t_ofile *ofile, struct segment_command *sg, int flags)
{
	uint32_t				i;
	struct section			*sect;

	i = 0;
	sg = swap_sg_cmd(sg, ofile->swap);
	sect = (void*)sg + sizeof(struct segment_command);
	if (!is_overflow((void*)sect, ofile->size))
		while (i++ < sg->nsects)
		{
			if (!ft_strlen(sect->sectname))
				continue ;
			if (!ft_strcmp(sect->segname, SEG_TEXT) &&
									!ft_strcmp(sect->sectname, SECT_TEXT))
				if (flags & T)
					return (swap_sect(sect, ofile->swap));
			if (!ft_strcmp(sect->segname, SEG_DATA) &&
									!ft_strcmp(sect->sectname, SECT_DATA))
				if (flags & D)
					return (swap_sect(sect, ofile->swap));
			sect = (void*)sect + sizeof(struct section);
			if (is_overflow((void*)sect, ofile->size))
				return (NULL);
		}
	return (NULL);
}
