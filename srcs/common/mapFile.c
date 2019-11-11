/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapFile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:32:49 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:52:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	fileDontExist(char *file) {
  ft_putstr_fd("nm: '", 2);
  ft_putstr_fd(file, 2);
  ft_putendl_fd("': No such file", 2);
  return 0;
}

int fileUnvalid(char *file, char *error) {
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(error, 2);
	
	return 0;
}

int		validFile(char *file, struct stat buf) {
	if (S_ISDIR(buf.st_mode)) {
		return fileUnvalid(file, ": is directory");
	} else if (S_ISCHR(buf.st_mode)) {
		return fileUnvalid(file, ": is character file");
	} else if (S_ISBLK(buf.st_mode)) {
		return fileUnvalid(file, ": is block");
	} else if (S_ISFIFO(buf.st_mode)) {
		return fileUnvalid(file, ": is fifo");
	} else if (S_ISLNK(buf.st_mode)) {
		return fileUnvalid(file, ": is link");
	} else if (S_ISSOCK(buf.st_mode)) {
		return fileUnvalid(file, ": is socket");
	}
	return 1;
}

int		mapFile(char *file, int flags, int (*f)(void*, int)) {
	int			fd;
	void		*ptr;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return 0;
	if (fstat(fd, &buf) == 0) {
		if (validFile(file, buf)) {
			if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) != MAP_FAILED) {
				f(ptr, flags);
				if (munmap(ptr, buf.st_size) < 0)
					exit(EXIT_FAILURE);
			}
		}
	}
	close(fd);
	return 0;
}
