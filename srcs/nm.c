/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/05 10:58:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_64(void *ptr, int flags) {
  (void)flags;
  struct mach_header_64	*header;

  header = (struct mach_header_64*)ptr;
  printf("ncmds: %u\n", header->ncmds);
}


void	handle_32(void *ptr, int flags) {
  (void)flags;
  struct mach_header	*header;

  header = (struct mach_header*)ptr;
  printf("ncmds: %u\n", header->ncmds);
}


int	nm(void *ptr, int flags) {
  (void)flags;
  unsigned int mn;

  mn = *(unsigned int*)ptr;

  if (mn == MH_CIGAM_64 || mn == MH_MAGIC_64) {
    printf("64-bits architecture\n");
    handle_64(ptr, flags);
  } else if (mn == MH_CIGAM || mn == MH_MAGIC) {
    printf("32-bits architecture\n");
    handle_32(ptr, flags);
  }
  return 0;
}
