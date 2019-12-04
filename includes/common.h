/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:58:20 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/04 14:43:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
	# include <mach-o/fat.h>
	# include <mach-o/loader.h>
	# include <mach-o/nlist.h>
	# include <mach-o/stab.h>
#else
	# include "./fat.h"
	# include "./loader.h"
	# include "./nlist.h"
	# include "./stab.h"
	# define AR_EFMT1 "#1/"
#endif

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include <ar.h>

typedef struct				s_flags {
	char					c;
	unsigned int			b;
}							t_flags;

int							getFlags(char **arg, unsigned int *opt, t_flags *arr, size_t len);


typedef struct				s_type {
	int						(*check)(void*);
	void					(*f)(void*, int, int);
}							t_type;

int							is_32(void *ptr);
int							is_64(void *ptr);
int							is_fat(void *ptr);
int							is_archive(void *ptr);

int							mapFile(char *file, int flags, int (*f)(void*, int));
void						print_ar_name(char *path, struct ar_hdr *hdr);

uint64_t					swp_int(uint64_t v);
struct load_command			*swap_load_cmd(struct load_command *lc, int swap);
struct load_command_64		*swap_load_cmd64(struct load_command_64 *lc, int swap);
struct symtab_command		*swap_symtab_cmd(struct symtab_command *sc, int swap);
struct symtab_command_64	*swap_symtab_cmd64(struct symtab_command_64 *sc, int swap);
struct nlist				swap_nlist(struct nlist symbol, int swap);
struct nlist_64				swap_nlist64(struct nlist_64 symbol, int swap);
struct segment_command_64	*swap_sg_cmd64(struct segment_command_64 *sg, int swap);
struct segment_command		*swap_sg_cmd(struct segment_command *sg, int swap);
struct section_64 *swap_sect64(struct section_64 *sg, int swap);
struct section *swap_sect(struct section *sg, int swap);
#endif
