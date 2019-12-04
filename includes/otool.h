/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:28:49 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/04 17:27:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

#include "common.h"

# define T (1 << 0) /*	Display the contents of the (__TEXT,__text) section. */

int		otool(char *file, void *ptr, int flags);

void	section_64(void *ptr, void *segment, int flags, int swap);
void	section_32(void *ptr, void *segment, int flags, int swap);
#endif
