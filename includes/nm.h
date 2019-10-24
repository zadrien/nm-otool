/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/24 20:12:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
	# include <mach-o/loader.h>
	# include <mach-o/nlist.h>
	# include <mach-o/stab.h>
#endif

#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"


# define A (1 << 0) /* all symbol entries flags */
# define G (1 << 1) /* only global (external) symbols*/
# define U (1 << 2) /* only undefined symbols*/


int		nm(void *ptr, int flags);
int		options(char **arg, unsigned int *opt);
/*************************/
/* LOAD_COMMAND FUNCTION */
/*************************/

void	symtab(void *ptr, void *stab, int flags);
char	*ft_type(unsigned int value);
#endif
