/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapFile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:32:49 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/04 18:32:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		fileDontExist(char *file)
{
	ft_putstr_fd("nm: '", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd("': No such file", 2);
	return (0);
}

int		fileUnvalid(char *file, char *error)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(error, 2);
	return (0);
}

int		validFile(char *file, struct stat buf)
{
	if (S_ISDIR(buf.st_mode))
		return (fileUnvalid(file, ": is directory"));
	else if (S_ISCHR(buf.st_mode))
		return (fileUnvalid(file, ": is character file"));
	else if (S_ISBLK(buf.st_mode))
		return (fileUnvalid(file, ": is block"));
	else if (S_ISFIFO(buf.st_mode))
		return (fileUnvalid(file, ": is fifo"));
	else if (S_ISLNK(buf.st_mode))
		return (fileUnvalid(file, ": is link"));
	else if (S_ISSOCK(buf.st_mode))
		return (fileUnvalid(file, ": is socket"));
	return (1);
}

t_ofile	*init() {
	t_ofile		*ofile;
	
	if (!(ofile = (t_ofile*)malloc(sizeof(t_ofile))))
		return (NULL);
	ofile->name = NULL;
	ofile->ptr = NULL;
	ofile->size = 0;
	ofile->swap = 0;
	return (ofile);
}

int		mapFile(char *file, int flags, int (*f)(char*, void*, int))
{
	int			fd;
	int			ret;
	void		*ptr;
	t_ofile		*ofile;
	struct stat	buf;

	ret = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (0);
	if (!(ofile = init()))
		return (NULL);
	ofile->name = file;
	if (fstat(fd, &buf) == 0)
		if (validFile(file, buf))
			ofile->size = buf.st_size;
			if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE,
							MAP_PRIVATE, fd, 0)) != MAP_FAILED)
			{
				ofile->ptr = ptr;
				ret = f(file, ptr, flags);
				if (munmap(ptr, buf.st_size) < 0)
					exit(EXIT_FAILURE);
			}
	close(fd);
	free(ofile);
	return (ret);
}
