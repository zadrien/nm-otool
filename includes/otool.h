/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:28:49 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/06 17:25:41 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

#include "common.h"

# define T (1 << 0) /*	Display the contents of the (__TEXT,__text) section. */

int		otool(t_ofile *ofile, int flags);

void	section_64(t_ofile *ofile, void *segment, int flags);
void	section_32(t_ofile *ofile, void *segment, int flags);
#endif
