/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stabs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:05:05 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/25 20:23:16 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

typedef struct	s_type {
	uint8_t		type;
	char		*str;
}				t_type;



char	*ft_type(unsigned int value) {
	int						i;
	static const	t_type	type[29] = { {N_GSYM, "GSYM"}, {N_FNAME, "FNAME"},{N_FUN, "FUN"},
{N_STSYM, "STSYM"},{N_LCSYM,"LCSYM"},{N_BNSYM,"BNSYM"},{N_OPT,"OPT"},{N_RSYM,"RSYM"},
{N_SLINE,"SLINE"},{N_ENSYM,"ENSYM"},{N_SSYM,"SSYM"},{N_SO,"SO"},{N_OSO,"OSO"},{N_LSYM,"LSYM"},
{N_BINCL,"BINCL"},{N_SOL,"SOL"},{N_PARAMS,"PARAMS"},{N_VERSION,"VERSION"},{N_OLEVEL,"OLEVEL"},
{N_PSYM,"PSYM"},{N_EINCL,"EINCL"},{N_ENTRY,"ENTRY"},{N_LBRAC,"LBRAC"},{N_EXCL,"EXCL"},
{N_RBRAC,"RBRAC"},{N_BCOMM,"BCOMM"},{N_ECOMM,"ECOMM"},{N_ECOML,"ECOML"},{N_LENG,"LENG"}};

	i = 0;
	while (i++ < 29) {
		if (!(value ^ type[i].type)) {
			return type[i].str;
		}
	}
	return NULL;
}
