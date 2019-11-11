/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:48:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	otool_32(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
	return;
}

void	otool_64(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
}

void	otool_ar(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
}

void	otool_fat(void *ptr, int flags) {
	(void)ptr;
	(void)flags;
}

int		start(void *ptr, int flags, char *file) {
	size_t			i;
	static t_type	arr[4] = { {is_32, otool_32}, {is_64, otool_64},
							   {is_archive, otool_ar}, {is_fat, otool_fat} };

	i = 0;
	if (ptr == NULL)
		return 0;
	while (i < 4) {
		if (arr[i].check(ptr)) {
			arr[i].f(ptr, flags);
			return 0;
		}
		i++;
	}
	printf("otool: %s: file format not found\n", file);
	return 0;
}

int		otool(char *file, int flags) {
	void	*ptr;
	ft_putendl(file);

	ptr = NULL;
	start(ptr, flags, file);
	return 0;
}
