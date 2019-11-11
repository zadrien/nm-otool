/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:58:20 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:52:47 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
	# include <mach-o/fat.h>
	# include <mach-o/loader.h>
	# include <mach-o/nlist.h>
	# include <mach-o/stab.h>
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

typedef struct		s_flags {
	char	c;
	unsigned int	b;
}					t_flags;

int		getFlags(char **arg, unsigned int *opt, t_flags *arr, size_t len);


typedef struct	s_type {
	int			(*check)(void*);
	void		(*f)(void*, int);
}				t_type;

int		is_32(void *ptr);
int		is_64(void *ptr);
int		is_fat(void *ptr);
int		is_archive(void *ptr);

int		mapFile(char *file, int flags, int (*f)(void*, int));

#endif
