/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:44:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 01:39:58 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*free_tiny_zone(t_tzone *tiny)
{
	if ((tiny->prev_zone || tiny->next_zone) && tiny->avail_bytes == TINY_DATA)
	{
		if (tiny->prev_zone && tiny->next_zone)
		{
			tiny->prev_zone->next_zone = tiny->next_zone;
			tiny->next_zone->prev_zone = tiny->prev_zone;
		}
		else if (tiny->next_zone)
		{
			g_menv->tiny = tiny->next_zone;
			g_menv->tiny->prev_zone = NULL;
		}
		else
			tiny->prev_zone->next_zone = NULL;
		//write(1, "MUNMAP TINY\n", 12);
		if (!(munmap((void*)tiny, TINY_ZONE)))
			return (NULL);
	}
	return (tiny);
}

static void		*free_tiny(void *zone, void *ptr)
{
	t_tzone		*tiny;
	t_tblock	*tblock;

	tiny = (t_tzone*)zone;
	tblock = (t_tblock*)((size_t)ptr - S_TBLOCK);
	//if (tblock->size <= 0)
	//	return (NULL);
	tiny->avail_bytes += tblock->size;
	tblock->size = -(tblock->size);
	/*if (tblock->next && tblock->next->size <= 0)
	{
		tblock->size += -((int)S_TBLOCK) + tblock->next->size;
		tblock->next = tblock->next->next;
		if (tblock->next)
			tblock->next->prev = tblock;
	}
	else if (tblock->prev && tblock->prev->size <= 0)
	{
		tblock->prev->size += -((int)S_TBLOCK) + tblock->size;
		tblock->prev->next = tblock->next;
		if (tblock->next)
			tblock->next->prev = tblock->prev;
	}*/
	return (free_tiny_zone(tiny));
}

static void		*free_small_zone(t_szone *small)
{
	if ((small->prev_zone || small->next_zone)
		&& small->avail_bytes == SMALL_DATA)
	{
		if (small->prev_zone && small->next_zone)
		{
			small->prev_zone->next_zone = small->next_zone;
			small->next_zone->prev_zone = small->prev_zone;
		}
		else if (small->next_zone)
		{
			g_menv->small = small->next_zone;
			g_menv->small->prev_zone = NULL;
		}
		else
			small->prev_zone->next_zone = NULL;
		//write(1, "MUNMAP SMALL\n", 13);
		if (!(munmap((void*)small, SMALL_ZONE)))
			return (NULL);
	}
	return (small);
}

static void		*free_small(void *zone, void *ptr)
{
	t_szone		*small;
	t_sblock	*sblock;

	small = (t_szone*)zone;
	sblock = (t_sblock*)((size_t)ptr - S_SBLOCK);
	if (sblock->size <= 0)
		return (NULL);
	small->avail_bytes += sblock->size;
	sblock->size = -(sblock->size);
	/*if (sblock->next && sblock->next->size < 0)
	{
		sblock->size += -((int)S_SBLOCK) + sblock->next->size;
		sblock->next = sblock->next->next;
		if (sblock->next)
			sblock->next->prev = sblock;
	}
	if (sblock->prev && sblock->prev->size < 0)
	{
		sblock->prev->size += -((int)S_SBLOCK) + sblock->size;
		sblock->prev->next = sblock->next;
		if (sblock->next)
			sblock->next->prev = sblock->prev;
	}*/
	return (free_small_zone(small));
}

static void		*free_blockzone(t_zone *zone, size_t data_zone)
{
	if ((zone->prev || zone->next) && zone->avail_bytes == data_zone)
	{
		if (zone->prev && tiny->next)
		{
			zone->prev->next = zone->next;
			zone->next->prev = zone->prev;
		}
		else if (tiny->next_zone)
		{
			g_menv->tiny = tiny->next_zone;
			g_menv->tiny->prev_zone = NULL;
		}
		else
			tiny->prev_zone->next_zone = NULL;
		//write(1, "MUNMAP TINY\n", 12);
		if (!(munmap((void*)tiny, TINY_ZONE)))
			return (NULL);
	}
	return (tiny);
}



void		*free_blockzone_ptr(t_zone *zone, void *ptr, size_t data_zone)
{
	t_block		*block;

	block = (t_block*)((size_t)ptr - S_BLOCK);
	if (block->size <= 0)
		return (NULL);
	zone->avail_bytes += block->size;
	block->size = -(block->size);
}


void			free(void *ptr)
{
	void	*zone;

	if (!ptr || !(zone = check_pointer(ptr)))
		return ;
	if (g_menv->curr_zone == 't' && !(free_tiny(zone, ptr)))
		return ;
	/*else if (g_menv->curr_zone == 's' && !(free_small(zone, ptr)))
		return ;
	else if (g_menv->curr_zone == 'l' && !(free_large(zone)))
		return ;
	(void)ptr;*/
	return ;
}
