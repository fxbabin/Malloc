/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_good_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:44:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/15 18:43:39 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			malloc_good_size(size_t size)
{
	size_t		tmp;

	tmp = 0;
	if (size < TINY_BLOCK)
	{
		tmp = size - size % TINY_MIN + TINY_MIN;
		return ((size % TINY_MIN == 0) ? size : tmp);
	}
	else if (size < SMALL_BLOCK)
	{
		tmp = size - size % SMALL_MIN + SMALL_MIN;
		return ((size % SMALL_MIN == 0) ? size : tmp);
	}
	tmp = size - size % PAGE_SIZE + PAGE_SIZE;
	return ((size % PAGE_SIZE == 0) ? size : tmp);
}

static size_t	check_blockzone(t_zone *zone, void *ptr)
{
	t_block		*block;

	while (zone)
	{
		block = (t_block*)((size_t)zone + S_ZONE);
		while (block)
		{
			if ((void*)((size_t)block + S_BLOCK) == ptr && block->size > 0)
				return ((size_t)block->size);
			block = block->next;
		}
		zone = zone->next;
	}
	return (0);
}

static size_t	check_large(void *ptr)
{
	t_zone		*zone;

	zone = g_menv->large;
	while (zone)
	{
		if ((void*)((size_t)zone + S_ZONE) == ptr)
			return (zone->avail_bytes);
		zone = zone->next;
	}
	return (0);
}

size_t			malloc_size_lock(void *ptr)
{
	size_t		ret;

	if (!ptr)
		return (0);
	if (!g_menv && init_menv() == -1)
		return (0);
	if (g_menv->tiny && (ret = check_blockzone(g_menv->tiny, ptr)))
		return (ret);
	else if (g_menv->small && (ret = check_blockzone(g_menv->small, ptr)))
		return (ret);
	else if ((ret = check_large(ptr)))
		return (ret);
	return (0);
}

size_t			malloc_size(void *ptr)
{
	size_t		ret;

	pthread_mutex_lock(&g_mutex);
	ret = malloc_size_lock(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
