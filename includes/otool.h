/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:28:49 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 17:22:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H
# include "common.h"

/*
** Display the contents of the (__TEXT,__text) section.
*/
# define T 1

/*
** Display the contents of the (__data,__data) section.
*/
# define D 2

typedef struct		s_section {
	void			*segment;
	void			*ptr;
}					t_section;

int					otool(t_ofile *ofile, int flags);
int					otool_32(t_ofile *ofile, int flags);
int					otool_64(t_ofile *ofile, int flags);
int					otool_ar(t_ofile *ofile, int flags);
int					otool_fat(t_ofile *ofile, int flags);

void				*sect_32(t_ofile *ofile, struct segment_command *sg,
																int flags);
void				*sect_64(t_ofile *ofile, struct segment_command_64 *sg,
																int flags);
t_lst				*save_section(t_lst **lst, struct load_command *lc, void *saved);
t_lst				*copy_section(t_lst **lst, t_section **new, void *saved, void *lc);

int					print_saved_section32(t_ofile *ofile, t_lst **lst);
int					print_saved_section64(t_ofile *ofile, t_lst **lst);

int					otool_ar(t_ofile *ofile, int flags);
int					otool_fat(t_ofile *ofile, int flags);
int					singleton(int value);
int					check_lc64(t_ofile *ofile, struct load_command *lc,
													t_lst **lst, int flags);
int					check_lc32(t_ofile *ofile, struct load_command *lc,
													t_lst **lst, int flags);
#endif
