/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:08:54 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 15:57:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

struct mach_header			*swap_mh(struct mach_header *mh, int swap)
{
	if (!swap)
		return (mh);
	mh->magic = swp_int(mh->magic);
	mh->ncmds = swp_int(mh->ncmds);
	mh->sizeofcmds = swp_int(mh->sizeofcmds);
	return (mh);
}

struct mach_header_64		*swap_mh64(struct mach_header_64 *mh, int swap)
{
	if (!swap)
		return (mh);
	mh->magic = swp_int(mh->magic);
	mh->ncmds = swp_int(mh->ncmds);
	mh->sizeofcmds = swp_int(mh->sizeofcmds);
	return (mh);
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

