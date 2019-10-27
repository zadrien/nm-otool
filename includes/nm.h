/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/27 11:56:46 by zadrien          ###   ########.fr       */
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


# define A (1 << 0) /*	all symbol entries flags		*/
# define G (1 << 1) /*	only global (external) symbols	*/
//# define U (1 << 2) /*	only undefined symbols			*/
# define P (1 << 3) /*	display in symbol-table order	*/
# define u (1 << 4) /*	display only undefined symbol	*/
# define U (1 << 5) /*	dont display undefined symbol	*/

int		nm(void *ptr, int flags);
int		options(char **arg, unsigned int *opt);
/*************************/
/* LOAD_COMMAND FUNCTION */
/*************************/

void	symtab_64(void *ptr, void *stab, int flags);
void	symtab_32(void *ptr, void *stab, int flags);
char	*ft_type(unsigned int value);


typedef struct		s_symbol {
	unsigned int	value;
	unsigned int	n_type;
	char			type;
	char			sect[3];
	char			desc[5];
	char			*symbol;
	char			stype;
	char			*name;

	struct s_symbol	*next;
}					t_symbol;


t_symbol	*newStruct();
void	*add(t_symbol **lst, t_symbol **elem, int (*f)(t_symbol*, t_symbol*));
int		cmpName(t_symbol *e1, t_symbol *e2);

char	symbol_type(unsigned int value, unsigned int sect);
void	print(t_symbol *lst);
#endif
