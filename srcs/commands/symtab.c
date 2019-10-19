/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/05 10:58:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


void	symtab(void *ptr, void *sc) { 
  unsigned int	i;
  struct symtab_command *stab;
  char			*strtable;
  struct nlist_64	*nl;
  char *str;
  i = 0;
  stab = (struct symtab_command*)sc;
  printf("nsyms: %u\n", stab->nsyms);
  nl = (void*)ptr + stab->symoff;
  strtable = (void*)ptr + stab->stroff;
  while (i < stab->nsyms) {
    str = strtable + nl[i].n_un.n_strx;
    if (ft_strcmp(str, "")) {
      printf("name: %s\n", (strtable + nl[i].n_un.n_strx));
      /* printf("n_type [%u]\n", nl[i].n_type); */
      /* printf("n_sect: [%u]\n", nl[i].n_sect); */
      /* printf("n_desc: [%u]\n", nl[i].n_desc); */
      /* printf("n_value: [%llu]\n", nl[i].n_value); */
      /* printf("==========\n"); */
    }
    i++;
  }
}
