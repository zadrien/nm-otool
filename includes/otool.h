/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:28:49 by zadrien           #+#    #+#             */
/*   Updated: 2019/11/11 19:49:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

#include "common.h"

# define T (1 << 0) /*	Display the contents of the (__TEXT,__text) section. */

int		otool(char *File, int flags);

#endif
