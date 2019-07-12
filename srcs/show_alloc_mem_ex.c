/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:15:20 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/12 23:21:42 by fbabin           ###   ########.fr       */
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
			ft_printf("%k%p%k - %k%p%k: %k%5d%k bytes\n", LYELLOW,
				(void*)((size_t)block + S_BLOCK), RESET, LYELLOW, (void*)((size_t)block->next), RESET, LRED, block->size, RESET);
		}
		else
		{
			ft_printf("%k%p%k - %k%p%k: %k%5d%k bytes\n", LYELLOW,
				(void*)((size_t)block + S_BLOCK), RESET, LYELLOW, (void*)((size_t)block->next), RESET, LGREEN, block->size, RESET, EOC);
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
		ft_printf("%s : %+k%p%k (avail: %lu)\n", str, LCYAN, zone, RESET, zone->avail_bytes);
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
		ft_printf("LARGE : %+k%p%k  (size: %zu)\n", LCYAN, zone, RESET, zone->avail_bytes);
		ft_printf("%k%p%k - %k%p%k: %k%4d%k bytes\n", LYELLOW, begin,
			RESET, LYELLOW, end, RESET, LRED, zone->avail_bytes, RESET, EOC);
		total += zone->avail_bytes;
		zone = zone->prev;
	}
	return (total);
}

void			show_alloc_mem_ex(void)
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
