/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:46:32 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/29 18:34:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_token(t_token **token)
{
	t_token *tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
}
