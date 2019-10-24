/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 10:38:09 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/20 10:58:54 by zadrien          ###   ########.fr       */
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

int start(char *file, int opt) {
	int				fd;
	void			*ptr;
	struct  stat	buf;
	
	if ((fd = open(file, O_RDONLY)) < 0)
		return fileDontExist(file);
	if (fstat(fd,&buf) != 0)
		return (0);

	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		printf("MAP_FAILED\n");
		return 0;
	}

	nm(ptr, opt);
  
	if (munmap(ptr, buf.st_size) < 0) {
		printf("munmap error\n");
		return 0;
	}
	return 0;
}
int     main(int ac, char **av)
{
  (void)ac;
  int			i;
  unsigned int	opt;
  char			dflt[7] = "a.out\0";

  opt = 0;
  if ((i = options(av, &opt)) == -1) {
	  return 0;
  }

  start(av[i] == NULL ? dflt : av[i], (int)opt);
  return (0);
}
