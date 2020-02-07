/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:32:49 by zadrien           #+#    #+#             */
/*   Updated: 2020/02/07 14:27:20 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_ofile	*init(void)
{
	t_ofile		*ofile;

	if (!(ofile = (t_ofile*)malloc(sizeof(t_ofile))))
		return (NULL);
	ofile->name = NULL;
	ofile->ptr = NULL;
	ofile->size = 0;
	ofile->swap = 0;
	return (ofile);
}

int		stat_file(int fd, t_ofile *ofile, int flags, int (*f)(t_ofile*, int))
{
	int			ret;
	void		*ptr;
	struct stat	buf;

	ret = 1;
	ptr = NULL;
	if (fstat(fd, &buf) == 0)
	{
		if (!valid_file(buf))
			file_unvalid(ofile->name,
						"The file was not recognized as a valid object file.");
		else if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE,
							MAP_PRIVATE, fd, 0)) != MAP_FAILED)
		{
			ofile->ptr = ptr;
			ofile->size = (void*)ptr + buf.st_size;
			ret = f(ofile, flags);
			if (munmap(ptr, buf.st_size) < 0)
				exit(EXIT_FAILURE);
		}
		else
			file_unvalid(ofile->name,
						"The file was not recognized as a valid object file.");
	}
	return (ret);
}

int		map_file(char *file, int flags, int (*f)(t_ofile*, int))
{
	int			fd;
	int			ret;
	t_ofile		*ofile;

	ret = 1;
	if ((fd = open(file, O_RDONLY)) <= 0)
		return (file_unvalid(file, "No such file or directory"));
	if (!(ofile = init()))
		return (1);
	ofile->name = file;
	ret = stat_file(fd, ofile, flags, f);
	close(fd);
	free(ofile);
	return (ret);
}
