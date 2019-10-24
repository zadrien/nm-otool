/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stabs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:05:05 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/24 23:04:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

typedef struct	s_type {
	uint8_t		type;
	char		*str;
}				t_type;



char	*ft_type(unsigned int value) {
	int						i;
	static const	t_type	type[2] = {
		{ N_SO, "SO" }, { N_OSO, "OSO" }
	};

	i = 0;
	while (i < 2) {
		if (!(value ^ type[i].type)) {
			printf("%s", type[i].str);
			return NULL;
		}
		i++;
	}
	return NULL;
}
