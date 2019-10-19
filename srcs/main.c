/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/05 10:58:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int     usage()
{
  ft_putstr_fd("nm ", 2);
  ft_putendl_fd("<executable>", 2);
  return (1);
}

int	fileDontExist(char *file) {
  ft_putstr_fd("nm: '", 2);
  ft_putstr_fd(file, 2);
  ft_putendl_fd("': No such file", 2);
  return 0;
}

int     main(int ac, char **av)
{
  (void)ac;
  int     fd;
  void    *ptr;
  struct  stat buf;
  char	dflt[7] = "a.out\0";
  
  if ((fd = open((av[1] != NULL ? av[1] : dflt), O_RDONLY)) < 0)
    return fileDontExist((av[1] != NULL ? av[1] : dflt));
  if (fstat(fd,&buf) != 0)
    return (0);

  if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
    printf("MAP_FAILED\n");
    return 0;
  }

  if (munmap(ptr, buf.st_size) < 0) {
    printf("munmap error\n");
    return 0;
  }
  
  return (0);
}
