/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:15:07 by zadrien           #+#    #+#             */
/*   Updated: 2020/01/27 15:58:00 by zadrien          ###   ########.fr       */
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

struct load_command		*swap_load_cmd(struct load_command *lc, int swap)
{
	if (!swap)
		return (lc);
	lc->cmd = swp_int(lc->cmd);
	lc->cmdsize = swp_int(lc->cmdsize);
	return (lc);
}
