/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:21 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/03 14:58:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include "common.h"

/*
** A - all symbol entries flags (OK)
** G - only global (external) symbols (NOPE)
** M - diplay string representation
** P - display in symbol-table order (OK)
** U_ONLY (u)- display only undefined symbol (OK)
** U - dont display undefined symbol (OK)
** N - Sorted numericaly (OK)
*/

# define A 1
# define G 2
# define M 4
# define P 8
# define U_ONLY 16
# define U 32
# define N 64
# define STR_EXT "external"
# define STR_N_EXT "non-external"
# define STR_LIBSYS " (from libSystem)"
# define SPACE_32B "        "
# define SPACE_64B "                "

int					nm(t_ofile *ofile, int flags);
int					options(char **arg, unsigned int *opt);

int					handle_32(t_ofile *ofile, int flags);
int					handle_64(t_ofile *ofile, int flags);
int					handle_fat(t_ofile *ofile, int flags);
int					handle_archive(t_ofile *ofile, int flags);

/*
**		SECTION
*/

typedef struct		s_sect {
	char			*segname;
	char			*sectname;
}					t_sect;

t_lst				*init_sectlst();
t_lst				*save_sect64(t_ofile *ofile, t_lst **lst, void *ptr);
t_lst				*save_sect32(t_ofile *ofile, t_lst **lst, void *ptr);
char				get_type(unsigned int type, unsigned int value,
															t_sect *section);
void				*get_section(t_lst *lst, size_t nbr);

/*
**		SYMBOL TABLE
*/

typedef struct		s_stab {
	uint8_t			type;
	char			*str;
}					t_stab;

int					symtab_64(t_ofile *ofile, struct symtab_command *symtab,
													t_lst *sects, int flags);
int					symtab_32(t_ofile *ofile, struct symtab_command *symtab,
													t_lst *sects, int flags);
char				*ft_type(unsigned int value);

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
	t_sect			*section;
	unsigned int	ext;

	char			*name;

	struct s_symbol *next;
}					t_symbol;

typedef struct		s_sort {
	unsigned int	flag;
	int				(*f)(t_symbol*, t_symbol*);
}					t_sort;

t_symbol			*new_symbol(struct nlist symbol,
												t_lst *sections, char *name);
t_symbol			*new_symbol64(t_ofile *ofile, struct nlist_64 symbol,
												t_lst *sections, char *name);
void				*free_symbol(t_symbol **lst);
void				*new_elem(t_symbol **lst, t_symbol *el, int flags);
int					print_symbols(t_symbol **lst, int flags);
void				print(t_symbol *el);
void			    print_value(t_symbol *s);
void				pad(char *str);
#endif
