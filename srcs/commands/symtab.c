/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/24 23:05:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void byteValue(unsigned int v, int mask) {
	unsigned char bytes[4];

	bytes[0] = (v >> 24) & mask;
	bytes[1] = (v >> 16) & mask;
	bytes[2] = (v >> 8) & mask;
	bytes[3] = v  & mask;

	printf("%x%x%x ", (unsigned char)bytes[1], (unsigned char)bytes[2], (unsigned char)bytes[3]);
}


/* void ft_type(unsigned int v, uint8_t mask) { */
/* 	uint8_t value; */

/* 	value = v & mask; */

/* 	while (!(mask & 0x01)) { */
/* 		value >>= 1; */
/* 		mask >>= 1; */
/* 	} */

/* 	printf("%02x ", value); */
/* } */

void	symtab(void *ptr, void *sc, int flags) { 
  unsigned int	i;
  struct symtab_command *stab;
  char			*strtable;
  struct nlist_64	*nl;
  char *str;
  i = 0;

  unsigned char b;
  stab = (struct symtab_command*)sc;
  //  printf("nsyms: %u\n", stab->nsyms);
  nl = (void*)ptr + stab->symoff;
  strtable = (void*)ptr + stab->stroff;
  while (i < stab->nsyms) {
	  b = (nl[i].n_type >> 24);
	  if (nl[i].n_type & N_STAB) {
		  if (flags & A) {
			  printf("%s ", ft_hex(nl[i].n_value));
//			  printf("%x", (nl[i].n_type );
			  ft_type(nl[i].n_type);
			  str = strtable + nl[i].n_un.n_strx;
			  printf(" - %s\n", str);
		  }
	  } else {
		  if (nl[i].n_sect != NO_SECT) {
			  if (!(flags & U)) {
				  printf("%s ", ft_hex(nl[i].n_value));
				  str = strtable + nl[i].n_un.n_strx;
				  printf("T %s\n", str);
			  }
		  } else { // NO_SECT undefined symbol
			  str = strtable + nl[i].n_un.n_strx;
			  printf(" U %s\n", str);
		  }
	  }
	  i++;
  }
}
