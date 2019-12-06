/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:34 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/06 18:18:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print64(t_ofile *ofile, struct section_64 *section)
{
	int					i;
	char				*str;
	unsigned long 		addr;

	i = 0;
	addr = section->addr;
	str = (void*)ofile->ptr + section->offset;
	while (i < (int)section->size)
	{
		if (ofile->swap && i % 4 == 0 && i > 0)
			ft_putchar(' ');
		if  (i % 16 == 0) {
			if (i > 0)
				ft_putendl("");
			ft_puthex((unsigned long long)addr, 8, 0);
			ft_putchar('\t');
		}
		ft_puthex((unsigned long long)(*str), 2, 0);
		if (!ofile->swap)
			ft_putchar(' ');
		addr++;
		str++;
		i++;

	}
	ft_putchar('\n');
}

void	print32(t_ofile *ofile, struct section *section)
{
	char			*str;
	int				i;
	unsigned long 	addr;

	i = 0;
	addr = section->addr;
	str = (void*)ofile->ptr + section->offset;
	while (i < (int)section->size)
	{
		if (ofile->swap && i % 4 == 0 && i > 0)
			ft_putchar(' ');
		if  (i % 16 == 0) {
			if (i > 0)
				ft_putendl("");
			ft_puthex((unsigned long long)addr, 8, 0);
			ft_putchar('\t');
		}
		ft_puthex((unsigned long long)(*str), 2, 0);
		if (!ofile->swap)
			ft_putchar(' ');
		addr++;
		str++;
		i++;
	}
	ft_putchar('\n');
}

void	section_64(t_ofile *ofile, void *segment, int flags)
{
	size_t						i;
	struct section_64			*sect;
	struct segment_command_64	*sg;
	struct section_64			*text;

	i = 0;
	text = NULL;
	sg = swap_sg_cmd64((struct segment_command_64*)segment, ofile->swap);
	sect = swap_sect64((void*)sg + sizeof(struct segment_command_64), ofile->swap);
	if ((unsigned long)(void*)sect >= (unsigned long)ofile->size)
		return ;
	while (i++ < sg->nsects) {
		if (!ft_strlen(sect->sectname))
			return ft_putendl_fd("Invalid data was encountered while parsing the file.", 2);
		if (flags & T)
			if (!ft_strcmp(sect->segname, SEG_TEXT) && !ft_strcmp(sect->sectname, SECT_TEXT))
				text = swap_sect64(sect, ofile->swap);
		if (((unsigned long)(void*)sect + sizeof(struct section_64)) >= (unsigned long)ofile->size)
			return ;
		sect = swap_sect64((void*)sect + sizeof(struct section_64), ofile->swap);
	}
	if (text != NULL)
	{
		ft_putendl("Contents of (__TEXT, __text) section:");
		print64(ofile, text);
	}
}



void	section_32(t_ofile *ofile, void *segment, int flags) {
	size_t					i;
	struct section			*sect;
	struct section			*text;
	struct segment_command	*sg;


	i = 0;
	text = NULL;
	sg = swap_sg_cmd(segment, ofile->swap);
	sect = (void*)sg + sizeof(struct segment_command);
	while (i++ < sg->nsects) {
		if (!ft_strlen(sect->segname))
			return ft_putendl_fd("Invalid data was encountered while parsing the file.", 2);
		if (flags & T)
			if (!ft_strcmp(sect->segname, SEG_TEXT) && !ft_strcmp(sect->sectname, SECT_TEXT))
				text = swap_sect(sect, ofile->swap);
		sect = (void*)sect + sizeof(struct section);
	}
	if (text)
	{
		ft_putendl("Contents of (__TEXT, __text) section:");
		print32(ofile, text);
	}
}

