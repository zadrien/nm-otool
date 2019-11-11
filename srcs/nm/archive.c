/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:47:26 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:15:29 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/* int is_archive(void *ptr) { */
/* 	if (ptr != NULL) */
/* 		if (!ft_strncmp((char*)ptr, ARMAG, SARMAG)) */
/* 			return 1; */
/* 	return 0; */
/* } */


void	printName(char *path, struct ar_hdr *hdr) {
	char	dst[17];

	ft_memset(dst, '\0', 17);
	if (!ft_strncmp(hdr->ar_name, AR_EFMT1, 3))
		ft_strcpy(dst, hdr->ar_fmag + 2);
	else
		ft_strncpy(dst, hdr->ar_name, 16);
	ft_putendl("");
	if (path)
		ft_putstr(path);
	ft_putstr("(");
	ft_putstr(dst);
	ft_putendl("):");
}
void	handle_archive(void *ptr, int flags)
{
	void			*h;
	struct ar_hdr	*hdr;
	
	hdr = (struct ar_hdr*)((void*)ptr + SARMAG);
	while (42) {
		hdr = (struct ar_hdr*)((void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size));
		if (ft_strlen(hdr->ar_name) == 0)
			break ;
		h = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if (is_32(h)) {
			printName(NULL, hdr);
			handle_32(h, flags);
		} else if (is_64(h)) {
			printName(NULL, hdr);
			handle_64(h, flags);
		} else if (is_fat(h)) {
			printName(NULL, hdr);
			handle_fat(h, flags);
		}
	}
}
