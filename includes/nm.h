/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/10 17:33:04 by zadrien          ###   ########.fr       */
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
# include <ar.h>
# include "libft.h"


# define A (1 << 0) /*	all symbol entries flags		*/
# define G (1 << 1) /*	only global (external) symbols	*/
# define M (1 << 2) /*	diplay string representation	*/
# define P (1 << 3) /*	display in symbol-table order	*/
# define u (1 << 4) /*	display only undefined symbol	*/
# define U (1 << 5) /*	dont display undefined symbol	*/
//# define SWAP_UL(x) ((x & 0xff00ff00ff00ff00ull) >> 8ull) | (( x & 0x00ff00ff00ff00ffull) <<8ull)



# define Swap8Bytes(val)  ( (((val) >> 56) & 0x00000000000000FF) | (((val) >> 40) & 0x000000000000FF00) | (((val) >> 24) & 0x0000000000FF0000) | (((val) >>  8) & 0x00000000FF000000) | (((val) <<  8) & 0x000000FF00000000) | (((val) << 24) & 0x0000FF0000000000) |(((val) << 40) & 0x00FF000000000000) | (((val) << 56) & 0xFF00000000000000) )

# define STR_EXT "external"
# define STR_N_EXT "non-external"
# define STR_LIBSYS " (from libSystem)"
# define SECT_CONST "__const"

int		nm(void *ptr, int flags);
int		options(char **arg, unsigned int *opt);

/*****************************/
/*			SECTION			 */
/*****************************/

typedef struct		s_lst {
	size_t			nbr;
	void			*ptr;
}					t_lst;

typedef struct		s_sect {
	char			*segname;
	char			*sectname;
}					t_sect;

void	printSec(t_lst *lst);
t_lst	*saveSect64(t_lst **lst, void *ptr);
char	getLetter(unsigned int type, t_sect *section);
void	*getSec(t_lst *lst, size_t nbr);
void	freeSection(t_lst **lst);

/*************************/
/* LOAD_COMMAND FUNCTION */
/*************************/

void	handle_64(void *ptr, int flags);

void	symtab_64(void *ptr, void *lc, t_lst *sects, int flags);
void	symtab_32(void *ptr, void *lc, t_lst *sects, int flags);
char	*ft_type(unsigned int value); // description

/*
** NEW SYMBOL REP
*/

/*****************************/
/*			SYMBOL			 */
/*****************************/

typedef struct		s_symbol {
	unsigned int	n_type;
	unsigned int	n_sect;

	char			*value;
	char			type;
	char			*sect;
	char			*desc;
	char			*stab;
	t_sect			*section; // if NULL, print (undefined)
	unsigned int	ext;

	char			*name;

	struct s_symbol *next;
}					t_symbol;

typedef struct		s_sort {
	unsigned int	flag;
	int				(*f)(t_symbol*, t_symbol*);
}					t_sort;

t_symbol	*newSymbol(struct nlist symbol, t_lst *sections, char *offset);
t_symbol	*newSymbol64(struct nlist_64 symbol, t_lst *sections, char *offset);
void		*newElem(t_symbol **lst, t_symbol *el, int flags);
void		*addLst(t_symbol **lst, t_symbol *elem, int (*f)(t_symbol*, t_symbol*));
int			sortedByName(t_symbol *e1, t_symbol* e2);
int			unSorted(t_symbol *e1, t_symbol *e2);
void		printSymbols(t_symbol *lst, int flags);
void		freeSymbol(t_symbol **lst);


/*************************/
/*	  ARCHIVE FUNCTION	 */
/*************************/

int		is_archive(void *ptr);
void	handle_archive(void *ptr, int flags);
#endif
