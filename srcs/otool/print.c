/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:45:39 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 15:41:17 by zadrien          ###   ########.fr       */
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

void	print64(t_ofile *ofile, char *addr, uint32_t offset, uint32_t size)
{
	uint64_t			i;
	char				*str;
	
	i = -1;
	str = (void*)ofile->ptr + offset;
	while (++i < size)
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
		if ((uint64_t)str >= (uint64_t)ofile->size)
			break ;				
	}
	ft_putchar('\n');
}

void	print32(t_ofile *ofile, uint32_t addr, uint32_t offset, uint32_t size)
{
	uint32_t		i;	
	char			*str;

	i = -1;
	str = (void*)ofile->ptr + offset;
	while (++i < size)
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
		if ((uint32_t)str >= (uint32_t)ofile->size)
			break ;

	}
	ft_putchar('\n');
}

void	print_saved_section64(t_ofile *ofile, t_lst *lst)
{
	uint8_t		i;
	t_section	*sect;
	struct	section_64	*s;

	i = 0;
	if (!lst)
		return ;
	sect = lst->ptr;
	if (lst->nbr > 0)
		if (!singleton(0))
		{
			ft_putstr(ofile->name);
			ft_putendl(":");
		}
	while(i++ < lst->nbr)
	{
		s = sect->ptr;
		content(s->segname, s->sectname);
		print64(ofile, (void*)s->addr, s->offset, s->size);
		sect++;
	}
}

void	print_saved_section32(t_ofile *ofile, t_lst *lst)
{
	uint8_t		i;
	t_section	*sect;
	struct	section	*s;

	i = 0;
	if (!lst)
		return ;
	sect = lst->ptr;
	if (lst->nbr > 0)
		if (!singleton(0))
		{
			ft_putstr(ofile->name);
			ft_putendl(":");
		}
	
	while(i++ < lst->nbr)
	{
		s = sect->ptr;
		content(s->segname, s->sectname);
		print32(ofile, s->addr, s->offset, s->size);
		sect++;
	}
}
