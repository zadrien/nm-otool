/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:46:41 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 16:22:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void print(t_symbol *el) {
	ft_putstr(el->type == 'U' ? "                ": el->value);
	ft_putchar(' ');
	if (el->type == '-')
		ft_putchar(el->type);
	else
		ft_putchar(el->ext ? el->type : el->type + 32);
	ft_putchar(' ');
	if (el->type == '-') {
		ft_putstr(el->sect);
		ft_putchar(' ');
		ft_putstr(el->desc);
		ft_putchar(' ');
		ft_putstr(el->stab);
		ft_putchar(' ');	
	}
	ft_putendl(el->name);
}

void printText(t_symbol *el) {
	t_sect *s;
	ft_putstr(el->type == 'U' ? "                " : el->value);
	if (el->section) {
		s = el->section ;
		ft_putstr(" (");
		ft_putstr(s->segname);
		ft_putchar(',');
		ft_putstr(s->sectname);
		ft_putstr(") ");
	} else {
		ft_putstr(el->type == 'U' ? " (undefined)" : " (?)");
	}
	ft_putchar(' ');
	ft_putstr(el->ext ? STR_EXT : STR_N_EXT);
	ft_putchar(' ');
	ft_putstr(el->name);
	ft_putendl(el->type == 'U' ? STR_LIBSYS : "");
	
}

void printSymbols(t_symbol *lst, int flags) {
	t_symbol	*tmp;
	
	if (!lst)
		return ;
	tmp = lst;
	while (tmp) {
		if (flags & M)
			printText(tmp);
		else
			print(tmp);
		tmp = tmp->next;
	}
}
