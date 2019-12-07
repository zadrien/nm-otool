/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 16:25:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H


# include "common.h"

# define A (1 << 0) /*	all symbol entries flags				*/
# define G (1 << 1) /*	only global (external) symbols			*/
# define M (1 << 2) /*	diplay string representation			*/
# define P (1 << 3) /*	display in symbol-table order	(OK)	*/
# define u (1 << 4) /*	display only undefined symbol	(OK)	*/
# define U (1 << 5) /*	dont display undefined symbol	(OK)	*/
# define n (1 << 6) /*	Sorted numericaly				(OK)	*/
# define STR_EXT "external"
# define STR_N_EXT "non-external"
# define STR_LIBSYS " (from libSystem)"
# define SPACE_32B "        "
# define SPACE_64B "                "


int		nm(t_ofile *ofile, int flags);
int		options(char **arg, unsigned int *opt);

void	handle_32(t_ofile *ofile, int flags);
void	handle_64(t_ofile *ofile, int flags);
void	handle_fat(t_ofile *ofile, int flags);
void	handle_archive(t_ofile *ofile, int flags);

/* ************************************************************************** */
/*										SECTION								  */
/* ************************************************************************** */

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
t_lst	*saveSect64(t_ofile *ofile, t_lst **lst, void *ptr);
t_lst	*saveSect32(t_ofile *ofile, t_lst **lst, void *ptr);
void	freeSection(t_lst **lst);
char	getLetter(unsigned int type, unsigned int value, t_sect *section);
void	freeSection(t_lst **lst);
void	*getSec(t_lst *lst, size_t nbr);

/* ************************************************************************** */
/*								SYMBOL TABLE								  */
/* ************************************************************************** */

void	symtab_64(void *ptr, void *lc, t_lst *sects, int flags, int swap);
void	symtab_32(void *ptr, void *lc, t_lst *sects, int flags, int swap);
char	*ft_type(unsigned int value); // description

typedef struct		s_symbol {
	uint8_t			n_type;
	unsigned int	n_sect;
	unsigned int	n_desc;
	unsigned int	n_value;
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
