/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/05 10:40:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
	# include <mach-o/loader.h>
	# include <mach-o/nlist.h>
	# include <mach-o/swap.h>
#endif

#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"


int	nm(void *ptr, int flags);

/*************************/
/* LOAD_COMMAND FUNCTION */
/*************************/

void	symtab(void *ptr, void *stab);
#endif
