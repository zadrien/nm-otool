/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:34 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/12 14:09:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	parseData_64(unsigned long long ptr, size_t len, size_t align) {
	size_t i;
	
	i = 0;
	while (i < len) {
		printf("%s  ", ft_hex(ptr, 8));
		ptr += align;
		printf("%s  ", ft_hex(ptr, 2));
		ptr += align;
		printf("%s  ", ft_hex(ptr, 16));
		ptr += align;
		printf("%s\n", ft_hex(ptr, 16));
		i += align * 3;
	}
}

void	parseSection_64(void *ptr, void *segment, int flags) {
	size_t						i;
	size_t						nsects;
	struct section_64			*sect;
	struct segment_command_64	*sg;

	(void)flags;
	(void)ptr;
	
	i = 0;
	sg = (struct segment_command_64*)segment;
	if (ft_strcmp(sg->segname, SEG_TEXT))
		return ;
	nsects = sg->nsects;
	sect = (void*)sg + sizeof(struct segment_command_64);
	while (i++ < nsects) {
		if (!ft_strcmp(sect->sectname, SECT_TEXT)) {
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putendl(") section:");
			parseData_64(sect->addr, sect->size, sect->align);
		}
		sect = (void*)sect + sizeof(struct section_64);
	}
}

