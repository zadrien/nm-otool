/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:28:49 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 13:48:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

#include "common.h"

# define T (1 << 0) /*	Display the contents of the (__TEXT,__text) section. */
# define d (1 << 1) /*	Display the contents of the (__data,__data) section. */

typedef struct s_section {
	void			*ptr;
	void			*safety;
}					t_section;


int		otool(t_ofile *ofile, int flags);

//void	section_64(t_ofile *ofile, void *segment, int flags);
//void	section_32(t_ofile *ofile, void *segment, int flags);

void	*sect_32(t_ofile *ofile, void *segment, int flags);
void	*sect_64(t_ofile *ofile, void *segment, int flags);
int		singleton(int value);

//t_section	*init_sect(void *ptr);
t_lst	*save_section(t_ofile *ofile, t_lst **lst, void *saved);
t_lst	*copy_section(t_lst **lst, t_section **new, void *saved);

void	print_saved_section32(t_ofile *ofile, t_lst *lst);
void	print_saved_section64(t_ofile *ofile, t_lst *lst);

int		otool_ar(t_ofile *ofile, int flags);
int		otool_fat(t_ofile *ofile, int flags);
#endif
