/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 18:25:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H


# include "common.h"

# define A (1 << 0) /*	all symbol entries flags		*/
# define G (1 << 1) /*	only global (external) symbols	*/
# define M (1 << 2) /*	diplay string representation	*/
# define P (1 << 3) /*	display in symbol-table order	*/
# define u (1 << 4) /*	display only undefined symbol	*/
# define U (1 << 5) /*	dont display undefined symbol	*/

# define STR_EXT "external"
# define STR_N_EXT "non-external"
# define STR_LIBSYS " (from libSystem)"
# define SECT_CONST "__const"



int		nm(void *ptr, int flags);
int		options(char **arg, unsigned int *opt);

/* typedef struct		s_flags { */
/* 	char	c; */
/* 	unsigned int	b; */
/* }					t_flags; */

/* int		is_32(void *ptr); */
/* int		is_64(void *ptr); */
/* int		is_fat(void *ptr); */
/* int		is_archive(void *ptr); */

void	handle_32(void *ptr, int flags, int swap);
void	handle_64(void *ptr, int flags, int swap);
void	handle_fat(void *ptr, int flags, int swap);
void	handle_archive(void *ptr, int flags, int swap);

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

t_lst	*init_sectlst();
void	printSec(t_lst *lst);
t_lst	*saveSect64(t_lst **lst, void *ptr);
t_lst	*saveSect32(t_lst **lst, void *ptr, int swap);
void	freeSection(t_lst **lst);
char	getLetter(unsigned int type, t_sect *section);
void	freeSection(t_lst **lst);
void	*getSec(t_lst *lst, size_t nbr);
/*****************************************/
/*				SYMBOL TABLE			 */
/*****************************************/

void	symtab_64(void *ptr, void *lc, t_lst *sects, int flags, int swap);
void	symtab_32(void *ptr, void *lc, t_lst *sects, int flags, int swap);
char	*ft_type(unsigned int value); // description

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
void print(t_symbol *el);

/*************************/
/*	  ARCHIVE FUNCTION	 */
/*************************/
#endif
