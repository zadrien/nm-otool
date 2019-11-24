/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:34 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/24 14:30:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print64(void *ptr, struct section_64 *section, int swap) {
	size_t				i;
	char				*str;
	unsigned long 		addr;

	i = 0;
	(void)swap;
	addr = section->addr;
	str = (void*)ptr + section->offset;
	while (i < section->size) {
		if  (i % 16 == 0) {
			if (i > 0)
				ft_putendl("");
			ft_puthex((unsigned long long)addr, 16, 0);
			ft_putchar('\t');
		}
		ft_puthex((unsigned long long)(*str), 2, 0);
		ft_putchar(' ');
		addr++;
		str++;
		i++;
	}
	ft_putchar('\n');
}

void	section_64(void *ptr, void *segment, int flags, int swap) {
	size_t						i;
	struct section_64			*sect;
	struct segment_command_64	*sg;


	i = 0;
	ft_putendl("???");
	sg = swap_sg_cmd64((struct segment_command_64*)segment, swap);
	sect = swap_sect64((void*)sg + sizeof(struct segment_command_64), swap);
	printf("%u\n", sg->nsects);
	while (i++ < sg->nsects) {
		if (ft_strcmp(sect->segname, SEG_TEXT))
			return ;
		if ((flags & T) && !ft_strcmp(sect->sectname, SECT_TEXT)) {
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putendl(") section:");
			print64(ptr, sect, swap);
		}
		sect = swap_sect64((void*)sect + sizeof(struct section_64), swap);
	}
}

void	print32(void *ptr, struct section *section, int swap) {
	char			*str;
	int				i;
	unsigned long 	addr;

	i = 0;
	(void)swap;
	addr = section->addr;
	str = (void*)ptr + (swap ? swp_int(section->offset) : section->offset);
	section->size = (swap ? swp_int(section->size) : section->size);
	while (i < (int)section->size) {
		if  (i % 16 == 0) {
			if (i > 0)
				ft_putendl("");
			ft_puthex((unsigned long long)addr, 8, 0);
			ft_putchar('\t');
		}
		ft_puthex((unsigned long long)(*str), 2, 0);
		addr++;
		str++;
		i++;
	}
	ft_putchar('\n');
}

void	section_32(void *ptr, void *segment, int flags, int swap) {
	size_t					i;
	struct section			*sect;
	struct segment_command	*sg;
	(void)ptr;
	i = 0;
	sg = swap_sg_cmd(segment, swap);
	sect = (void*)sg + sizeof(struct segment_command);
	printf("%u\n",sg->nsects);
	if (ft_strcmp(sg->segname, SEG_TEXT))
		return ;	
	while (i++ < sg->nsects) {
		ft_putendl(sect->sectname);
		if ((flags & T) && !ft_strcmp(sect->sectname, SECT_TEXT)) {
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putendl(") section:");
			print32(ptr, sect, swap);
		}
		sect = (void*)sect + sizeof(struct section);
	}
}

