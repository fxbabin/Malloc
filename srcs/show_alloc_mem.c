/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:45:09 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 23:52:47 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	show_zone(t_zone *zone)
{
	t_block		*block;
	size_t		total;
	int			i;

	i = -1;
	total = 0;
	block = (t_block*)((size_t)zone + S_ZONE);
	while (block)
	{
		if (block->size > 0)
		{
			total += (size_t)block->size;
			ft_printf("%d :: %p - %p: %4d bytes\n", ++i,
				(void*)((size_t)block + S_BLOCK),
				(void*)((size_t)block->next), block->size);
		}
		block = block->next;
	}
	return (total);
}

static size_t	show_full_zone(t_zone *zone, const char *str)
{
	size_t		total;

	total = 0;
	while (zone && zone->next)
		zone = zone->next;
	while (zone)
	{
		ft_printf("%d\n", zone->avail_bytes);
		ft_printf("%s : %p\n", str, zone);
		total += show_zone(zone);
		zone = zone->prev;
	}
	return (total);
}

static size_t	show_large_zone(t_zone *zone)
{
	void		*begin;
	void		*end;
	size_t		total;

	total = 0;
	while (zone && zone->next)
		zone = zone->next;
	while (zone)
	{
		begin = (void*)((size_t)zone + S_ZONE);
		end = (void*)((size_t)begin + zone->avail_bytes);
		ft_printf("LARGE : %p\n", zone);
		ft_printf("%p - %p: %4d bytes\n", begin, end, zone->avail_bytes);
		total += zone->avail_bytes;
		zone = zone->prev;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t		total;

	if (!g_menv)
		return ;
	total = 0;
	total += show_full_zone(g_menv->tiny, "TINY");
	total += show_full_zone(g_menv->small, "SMALL");
	total += show_large_zone(g_menv->large);
	ft_printf("Total : %zu bytes\n", total);
}
