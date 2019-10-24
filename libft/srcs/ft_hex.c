/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:08:47 by zadrien           #+#    #+#             */
/*   Updated: 2019/10/24 17:13:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int rec_itoh(char *str, long int nbr, int k) {

	long int res;
	int modulo;
	int y;
	res = nbr / 16;
	modulo = nbr % 16;

	if (k == -1)
		return 1;
	
	if (modulo <= 9) {
		str[k] = 48 + modulo;
	} else if (modulo >= 10 && modulo <= 15) {
		y = modulo % 10;
		str[k] = 97 + y;
	} else
		return 0;

	if (rec_itoh(str, res, --k) == 0)
		return 0;
	return 1;
}

char *ft_hex(long int v) {

	int i;
	char	*str;

	if (!(str = (char*)malloc(sizeof(char)*16)))
		return NULL;
	i = 16;
	str[i--] = '\0';
	if (!rec_itoh(str, v, i))
		return NULL;
	return str;
}
