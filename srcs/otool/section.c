/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:34 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/22 10:34:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print64(void *ptr, struct section_64 *section) {
	size_t					i;
	unsigned long 		addr;
	char	*str;

	i = 0;
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

void	section_64(void *ptr, void *segment, int flags) {
	size_t						i;
	struct section_64			*sect;
	struct segment_command_64	*sg;

	(void)flags;
	i = 0;
	sg = (struct segment_command_64*)segment;
	sect = (void*)sg + sizeof(struct segment_command_64);
	while (i++ < sg->nsects) {
		if (ft_strcmp(sect->segname, SEG_TEXT))
			return ;
		if ((flags & T) && !ft_strcmp(sect->sectname, SECT_TEXT)) {
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putendl(") section:");
			print64(ptr, sect);
		}
		sect = (void*)sect + sizeof(struct section_64);
	}
}

void	print32(void *ptr, struct section *section) {
	char			*str;
	size_t				i;
	unsigned long 	addr;

	i = 0;
	addr = section->addr;
	str = (void*)ptr + section->offset;
	while (i < section->size) {
		if  (i % 16 == 0) {
			if (i > 0)
				ft_putendl("");
			ft_puthex((unsigned long long)addr, 8, 0);
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

void	section_32(void *ptr, void *segment, int flags) {
	size_t					i;
	struct section			*sect;
	struct segment_command	*sg;

	i = 0;
	sg = (struct segment_command*)segment;
	sect = (void*)sg + sizeof(struct segment_command);
	while (i++ < sg->nsects) {
		if (ft_strcmp(sg->segname, SEG_TEXT))
			return ;
		if ((flags & T) && !ft_strcmp(sect->sectname, SECT_TEXT)) {
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putendl(") section:");
			print32(ptr, sect);
		}
		sect = (void*)sect + sizeof(struct section);
	}
}

