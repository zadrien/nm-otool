/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:47:26 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/23 13:46:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


void	handle_archive(void *ptr, int flags, int swap)
{
	void			*h;
	struct ar_hdr	*hdr;
	
	(void)swap;
	hdr = (struct ar_hdr*)((void*)ptr + SARMAG);
	while (42) {
		hdr = (struct ar_hdr*)((void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size));
		if (ft_strlen(hdr->ar_name) == 0)
			break ;
		h = (void*)hdr + sizeof(struct ar_hdr) + ft_atoi(hdr->ar_name + 3);
		if (is_32(h)) {
			print_ar_name(NULL, hdr);
			handle_32(h, flags, swap);
		} else if (is_64(h)) {
			print_ar_name(NULL, hdr);
			handle_64(h, flags, swap);
		} else if (is_fat(h)) {
			print_ar_name(NULL, hdr);
			handle_fat(h, flags, swap);
		}
	}
}
