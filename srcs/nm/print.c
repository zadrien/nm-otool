/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:46:41 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/08 13:56:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print(t_symbol *el)
{
	print_value(el);
	ft_putchar(' ');
	if (el->type == '-')
		ft_putchar(el->type);
	else
		ft_putchar(el->ext ? el->type : el->type + 32);
	ft_putchar(' ');
	if (el->type == '-')
	{
		ft_putstr(el->sect);
		ft_putchar(' ');
		ft_putstr(el->desc);
		pad(el->stab);
	}
	ft_putstr(el->name);
	ft_putchar('\n');
}

void	section(unsigned int type, unsigned int desc)
{
	if ((type & N_TYPE) == N_ABS)
	{
		ft_putstr(" (absolute)");
		return ;
	}
	else if ((type & N_TYPE) == N_PBUD)
	{
		ft_putstr(" (prebound ");
	}
	else
		ft_putstr(" (");
	if ((desc & REFERENCE_TYPE) == REFERENCE_FLAG_UNDEFINED_LAZY)
		ft_putstr("undefined [lazy bound])");
	else if ((desc & REFERENCE_TYPE) == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
		ft_putstr("undefined [private lazy bound])");
	else if ((desc & REFERENCE_TYPE) ==
	REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
		ft_putstr("undefined [private])");
	else
		ft_putstr("undefined)");
}

void	print_text(t_symbol *el)
{
	t_sect		*s;

	print_value(el);
	if (el->section)
	{
		s = el->section;
		ft_putstr(" (");
		ft_putstr(s->segname);
		ft_putchar(',');
		ft_putstr(s->sectname);
		ft_putstr(") ");
	}
	else
		section(el->n_type, el->n_desc);
	ft_putchar(' ');
	ft_putstr(el->ext ? STR_EXT : STR_N_EXT);
	ft_putchar(' ');
	ft_putstr(el->name);
	ft_putstr(el->type == 'U' ? STR_LIBSYS : "");
	ft_putchar('\n');
}

int		print_symbols(t_symbol **lst, int flags)
{
	t_symbol	*tmp;
	void		(*f)(t_symbol*);

	if (!(*lst))
		return (1);
	f = (flags & M) ? print_text : print;
	tmp = *lst;
	while (tmp)
	{
		f(tmp);
		tmp = tmp->next;
	}
	free_symbol_lst(lst);
	return (0);
}
