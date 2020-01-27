/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:45:39 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 14:18:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	content(char *seg, char *sect)
{
	ft_putstr("Contents of (");
	ft_putstr(seg);
	ft_putchar(',');
	ft_putstr(sect);
	ft_putendl(") section");
}

void	print64(t_ofile *ofile, struct section_64 *section)
{
	uint64_t			i;
	char				*str;
	char		 		*addr;
	
	i = 0;
	addr = (void*)section->addr;
	str = (void*)ofile->ptr + section->offset;
	while (i < section->size)
	{
		if (ofile->swap && i % 4 == 0 && i > 0)
			ft_putchar(' ');
		if  (i % 16 == 0) {
			if (i > 0) {
				ft_putendl("");
			}
			ft_puthex((unsigned long)addr, 16, 0);
			ft_putchar('\t');
		}
		ft_puthex((uint8_t)(*str), 2, 0);
		if (!ofile->swap)
			ft_putchar(' ');
		addr++;
		str++;
		i++;
		if ((uint64_t)str >= (uint64_t)ofile->size)
			break ;
	}
	ft_putchar('\n');
}

void	print32(t_ofile *ofile, struct section *section)
{
	uint32_t		i;	
	char			*str;
	uint32_t	 	addr;

	i = 0;
//	section = swap_sect(section, ofile->swap);
	addr = section->addr;
	str = (void*)ofile->ptr + section->offset;
	while (i < section->size)
	{
		if (ofile->swap && i % 4 == 0 && i > 0)
			ft_putchar(' ');
		if  (i % 16 == 0) {
			if (i > 0)
				ft_putendl("");
			ft_puthex((unsigned long)addr, 8, 0);
			ft_putchar('\t');
		}
		ft_puthex((unsigned long long)(*str), 2, 0);
		if (!ofile->swap)
			ft_putchar(' ');
		addr++;
		str++;
		i++;
		if ((uint32_t)str >= (uint32_t)ofile->size)
			break ;

	}
	ft_putchar('\n');
}

void	print_saved_section64(t_ofile *ofile, t_lst *lst)
{
	uint8_t		i;
	t_lst		*tmp;
	t_section	*sect;
	struct	section_64	*s;

	i = 0;
	if (!lst)
		return ;
	tmp = lst;
	sect = tmp->ptr;
	if (tmp->nbr > 0)
		if (!singleton(0)) {
			ft_putstr(ofile->name);
			ft_putendl(":");
		}
	while(i < lst->nbr) {
		s = sect->ptr;
		content(s->segname, s->sectname);
		print64(ofile, s);
		sect++;
		i++;
	}
}

void	print_saved_section32(t_ofile *ofile, t_lst *lst)
{
	uint8_t		i;
	t_lst		*tmp;
	t_section	*sect;
	struct	section	*s;

	i = 0;
	if (!lst)
		return ;
	tmp = lst;
	sect = tmp->ptr;
	if (tmp->nbr > 0)
		if (!singleton(0)) {
			ft_putstr(ofile->name);
			ft_putendl(":");
		}
	
	while(i < lst->nbr) {
		s = (struct section*)sect->ptr;
		content(s->segname, s->sectname);
		print32(ofile, s);
		sect++;
		i++;
	}
}
