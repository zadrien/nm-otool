/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:08:54 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 13:18:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint64_t				swp_int(uint64_t v)
{
	return (((v >> 24) & 0xff) | ((v << 8) & 0xff0000) |
			((v >> 8) & 0xff00) | ((v << 24) & 0xff000000));
}

struct load_command		*swap_load_cmd(struct load_command *lc, int swap)
{
	if (!swap)
		return (lc);
	lc->cmd = swp_int(lc->cmd);
	lc->cmdsize = swp_int(lc->cmdsize);
	return (lc);
}

struct symtab_command	*swap_symtab_cmd(struct symtab_command *sc, int swap) {
	if (!swap)
		return (sc);
	sc->cmd = swp_int(sc->cmd);
	sc->cmdsize = swp_int(sc->cmdsize);
	sc->symoff = swp_int(sc->symoff);
	sc->nsyms = swp_int(sc->nsyms);
	sc->stroff = swp_int(sc->stroff);
	sc->strsize = swp_int(sc->strsize);
	return (sc);
}

struct nlist			swap_nlist(struct nlist symbol, int swap)
{
	if (!swap)
		return (symbol);
	symbol.n_value = swp_int(symbol.n_value);
	symbol.n_un.n_strx = swp_int(symbol.n_un.n_strx);
	return (symbol);
}

struct nlist_64			swap_nlist64(struct nlist_64 symbol, int swap)
{
	if (!swap)
		return (symbol);
	symbol.n_value = swp_int(symbol.n_value);
	symbol.n_un.n_strx = swp_int(symbol.n_un.n_strx);
	return (symbol);
}

