/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_zones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:44:16 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 00:44:11 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zone		*lzonecreate(size_t size)
{
	t_zone		*ret;

	if (!(ret = (t_zone*)mmap(0, PAGE_SIZE + size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	ret->next = NULL;
	ret->prev = NULL;
	ret->avail_bytes = size;
	return (ret);
}

void				*lzonepushfront(t_zone **zone, size_t size)
{
	t_zone		*new;

	if (!zone)
		return (NULL);
	if (*zone)
	{
		if (!(new = lzonecreate(size)))
			return (NULL);
		new->next = (*zone);
		(*zone)->prev = new;
		(*zone) = new;
	}
	else
	{
		if (!(new = lzonecreate(size)))
			return (NULL);
		(*zone) = new;
	}
	return (*zone);
}
