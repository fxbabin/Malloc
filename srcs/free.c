/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:44:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 23:11:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zone	*free_blockzone(t_zone **g_zone, t_zone *zone)
{
	size_t		data_zone;
	size_t		min_zone;
	size_t		size_zone;

	data_zone = (g_menv->curr_zone == 't') ? TINY_DATA : SMALL_DATA;
	min_zone = (g_menv->curr_zone == 't') ? TINY_MIN : SMALL_MIN;
	size_zone = (g_menv->curr_zone == 't') ? TINY_ZONE : SMALL_ZONE;
	if ((zone->prev || zone->next) && zone->avail_bytes == data_zone)
	{
		if (zone->prev && zone->next)
		{
			zone->prev->next = zone->next;
			zone->next->prev = zone->prev;
		}
		else if (zone->next != 0x0)
		{
			(*g_zone) = zone->next;
			(*g_zone)->prev = NULL;
		}
		else
			zone->prev->next = NULL;
		if ((munmap((void*)zone, size_zone)) == -1)
			return (NULL);
	}
	return (zone);
}

static void		*free_blockzone_ptr(t_zone **g_zone, t_zone *zone, void *ptr)
{
	t_block		*block;

	block = (t_block*)((size_t)ptr - S_BLOCK);
	if (block->size <= 0)
		return (NULL);
	zone->avail_bytes += (size_t)block->size + S_BLOCK;
	block->size = -(block->size);
	if (block->next && block->next->size <= 0)
	{
		block->size += -((int)S_BLOCK) + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
	}
	if (block->prev && block->prev->size <= 0)
	{
		block->prev->size += -((int)S_BLOCK) + block->size;
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
	}
	return (free_blockzone(g_zone, zone));
}

static void		*free_large(t_zone *zone)
{
	if (zone->prev && zone->next)
	{
		zone->prev->next = zone->next;
		zone->next->prev = zone->prev;
	}
	else if (zone->next)
	{
		g_menv->large = zone->next;
		g_menv->large->prev = NULL;
	}
	else if (zone->prev)
		zone->prev->next = NULL;
	else
		g_menv->large = NULL;
	if ((munmap(zone, PAGE_SIZE + zone->avail_bytes)) == -1)
		return (NULL);
	return ((void*)g_menv->large);
}

void			free_lock(void *ptr)
{
	void	*zone;

	if (!ptr || !(zone = check_pointer(ptr)))
		return ;
	if (g_menv->curr_zone == 't'
		&& !(free_blockzone_ptr(&g_menv->tiny, zone, ptr)))
		return ;
	if (g_menv->curr_zone == 's'
		&& !(free_blockzone_ptr(&g_menv->small, zone, ptr)))
		return ;
	else if (g_menv->curr_zone == 'l' && !(free_large(zone)))
		return ;
	return ;
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	//ft_dprintf(2, "FREE B\n");
	free_lock(ptr);
	//ft_dprintf(2, "FREE E\n");
	pthread_mutex_unlock(&g_mutex);
}
