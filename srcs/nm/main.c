/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:12:28 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 20:08:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_flags	flags[6] = { { 'a', A }, { 'g', G },  { 'u', u },
							 { 'U', U }, {'p', P }, {'m', M} };
int     usage()
{
  ft_putstr_fd("nm ", 2);
  ft_putendl_fd("<executable>", 2);
  return (1);
}

int     main(int ac, char **av)
{
  (void)ac;
  int			i;
  unsigned int	opt;
  char			dflt[7] = "a.out\0";

  opt = 0;
  if ((i = getFlags(av, &opt, flags, 6)) == -1) {
	  return 0;
  }
  mapFile(av[i] == NULL ? dflt : av[i], opt, nm);
  return (0);
}
