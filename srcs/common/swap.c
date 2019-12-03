/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:08:54 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/03 20:59:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint64_t					swp_int(uint64_t v)
{
	return (((v >> 24) & 0xff) | // move byte 3 to byte 0
                    ((v << 8) & 0xff0000) | // move byte 1 to byte 2
                    ((v >> 8) & 0xff00) | // move byte 2 to byte 1
			((v << 24) & 0xff000000));
}

struct load_command			*swap_load_cmd(struct load_command *lc, int swap)
{
	if (!swap)
		return (lc);
	lc->cmd = swp_int(lc->cmd);
	lc->cmdsize = swp_int(lc->cmdsize);
	return (lc0;
}

struct symtab_command		*swap_symtab_cmd(struct symtab_command *sc, int swap) {
	if (!swap)
		return (sc);
	sc->cmd = swp_int(sc->cmd);
	sc->cmdsize = swp_int(sc->cmdsize);
	sc->symoff = swp_int(sc->symoff);
	sc->nsyms = swp_int(sc->nsyms);
	sc->stroff = swp_int(sc->stroff);
	sc->strsize = swp_int(sc->strsize);
	return sc;
}

struct nlist				swap_nlist(struct nlist symbol, int swap)
{
	if (!swap)
		return (symbol);
	symbol.n_value = swp_int(symbol.n_value);
	symbol.n_un.n_strx = swp_int(symbol.n_un.n_strx);
	return (symbol);
}

struct nlist_64				swap_nlist64(struct nlist_64 symbol, int swap)
{
	if (!swap)
		return symbol;
	symbol.n_value = swp_int(symbol.n_value);
	symbol.n_un.n_strx = swp_int(symbol.n_un.n_strx);
	return symbol;
}

struct section_64			*swap_sect64(struct section_64 *sg, int swap)
{
	if (!swap)
		return (sg);
	sg->addr = swp_int(sg->addr);
	sg->size = swp_int(sg->size);
	sg->offset = swp_int(sg->offset);
	sg->align = swp_int(sg->align);
	sg->reloff = swp_int(sg->reloff);
	sg->nreloc = swp_int(sg->nreloc);
	sg->flags = swp_int(sg->flags);
	return (sg);
}

struct section				*swap_sect(struct section *sg, int swap)
{
	if (!swap)
		return (sg);
	sg->addr = swp_int(sg->addr);
	sg->size = swp_int(sg->size);
	sg->offset = swp_int(sg->offset);
	sg->align = swp_int(sg->align);
	sg->reloff = swp_int(sg->reloff);
	sg->nreloc = swp_int(sg->nreloc);
	sg->flags = swp_int(sg->flags);
	return sg;
}

struct segment_command_64	*swap_sg_cmd64(struct segment_command_64 *sg, int swap)
{
	if (!swap)
		return (sg);
	sg->cmd = swp_int(sg->cmd);
	sg->cmdsize = swp_int(sg->cmdsize);
	sg->vmaddr = swp_int(sg->vmaddr);
	sg->vmsize = swp_int(sg->vmsize);
	sg->fileoff = swp_int(sg->fileoff);
	sg->filesize = swp_int(sg->filesize);
	sg->nsects = swp_int(sg->nsects);
	sg->flags = swp_int(sg->flags);
	return (sg);
}

struct segment_command		*swap_sg_cmd(struct segment_command *sg, int swap)
{
	if (!swap)
		return (sg);
	sg->vmaddr = swp_int(sg->vmaddr);
	sg->vmsize = swp_int(sg->vmsize);
	sg->fileoff = swp_int(sg->fileoff);
	sg->filesize = swp_int(sg->filesize);
	sg->nsects = swp_int(sg->nsects);
	sg->flags = swp_int(sg->flags);
	return (sg);
}
