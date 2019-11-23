/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkFile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:03:43 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 18:31:08 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		is_32(void *ptr) {
	unsigned int	mn;

	mn = *(unsigned int*)ptr;
	if (mn == MH_CIGAM)
		return 1;
	if (mn == MH_CIGAM || mn == MH_MAGIC)
		return 0;
	return -1;
}

int		is_64(void *ptr) {
	unsigned int	mn;

	mn = *(unsigned int*)ptr;
	if (mn == MH_CIGAM_64)
		return 1;
	if (mn == MH_MAGIC_64)
		return 0;
	return -1;
}

int is_archive(void *ptr) {
	if (ptr != NULL)
		if (!ft_strncmp((char*)ptr, ARMAG, SARMAG))
			return 1;
	return -1;
}

int		is_fat(void *ptr) {
	unsigned int magic;

	magic = *(unsigned int*)ptr;
	if (magic == FAT_CIGAM)
		return 1;
	if (magic == FAT_CIGAM || magic == FAT_MAGIC)
		return 1;
	return -1;
}

