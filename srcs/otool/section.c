/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:34 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 14:12:14 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
void	print_section(struct section_64 *s) {
	printf("\t-------SECTION (%s, %s)-------\n", s->sectname, s->segname);
	printf("section size: %llu", s->size);
}

void	*sect_64(t_ofile *ofile, void *segment, int flags) {
	uint32_t					i;
	struct section_64			*sect;
	struct segment_command_64	*sg;
	
	i = 0;
	sg = swap_sg_cmd64((struct segment_command_64*)segment, ofile->swap);
	sect = swap_sect64((void*)sg + sizeof(struct segment_command_64), ofile->swap);
	if ((unsigned long)(void*)sect >= (unsigned long)ofile->size)
		return (NULL);
	while (i++ < sg->nsects) {
		if (!ft_strlen(sect->sectname)) {
//			ft_putendl_fd("Invalid data was encountered while parsing the file.", 2);
//			return (NULL);
			continue ;
		}
		if (!ft_strcmp(sect->segname, SEG_TEXT) && !ft_strcmp(sect->sectname, SECT_TEXT))
			if (flags & T)
				return swap_sect64(sect, ofile->swap);
		if (!ft_strcmp(sect->segname, SEG_DATA) && !ft_strcmp(sect->sectname, SECT_DATA))
			if (flags & d)
				return swap_sect64(sect, ofile->swap);
		sect = (void*)sect + sizeof(struct section_64);
	}
	return (NULL);
}

void	*sect_32(t_ofile *ofile, void *segment, int flags) {
	uint32_t				i;
	struct section			*sect;
	struct segment_command	*sg;
	
	i = 0;
	sg = swap_sg_cmd(segment, ofile->swap);
	sect = (void*)segment + sizeof(struct segment_command);
	if ((unsigned long)(void*)sect >= (unsigned long)ofile->size)
		return (NULL);
	while (i++ < sg->nsects)
	{
		if (!ft_strlen(sect->sectname))
			continue ;
		if (flags & T)
			if (!ft_strcmp(sect->segname, SEG_TEXT) && !ft_strcmp(sect->sectname, SECT_TEXT)) {
				return swap_sect(sect, ofile->swap);
			}
		if (flags & d)
			if (!ft_strcmp(sect->segname, SEG_DATA) && !ft_strcmp(sect->sectname, SECT_DATA)) {
				return swap_sect(sect, ofile->swap);
			}
		sect = (void*)sect + sizeof(struct section);
	}
	return (NULL);
}
