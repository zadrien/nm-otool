/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:15:07 by zadrien           #+#    #+#             */
/*   Updated: 2019/12/07 16:10:58 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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
	return (sg);
}

struct segment_command_64	*swap_sg_cmd64(struct segment_command_64 *sg, int swap)
{
	if (!swap)
		return (sg);
//	sg->cmd = swp_int(sg->cmd);
//	sg->cmdsize = swp_int(sg->cmdsize);
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
