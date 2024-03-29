/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:47:13 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/15 20:23:33 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					init_menv(void)
{
	if ((g_menv = (t_menv*)mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_dprintf(2, "Error :: g_menv mmap failed (init_menv)\n");
		return (-1);
	}
	g_menv->tiny = NULL;
	g_menv->small = NULL;
	g_menv->large = NULL;
	g_menv->curr_zone = 'z';
	return (0);
}

static t_zone		*zonecreate(size_t size, size_t avail)
{
	t_zone		*ret;
	t_block		*curr;

	if ((ret = (t_zone*)mmap(0, size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	ret->avail_bytes = avail;
	ret->next = NULL;
	ret->prev = NULL;
	curr = (t_block*)((size_t)ret + S_ZONE);
	curr->prev = NULL;
	curr->size = -((int)(avail - S_BLOCK));
	curr->next = NULL;
	return (ret);
}

void				*zonepushfront(t_zone **zone, size_t size, size_t avail)
{
	t_zone		*new;

	if (!zone)
		return (NULL);
	if (*zone)
	{
		if (!(new = zonecreate(size, avail)))
			return (NULL);
		new->next = (*zone);
		(*zone)->prev = new;
		(*zone) = new;
	}
	else
	{
		if (!(new = zonecreate(size, avail)))
			return (NULL);
		(*zone) = new;
	}
	return (*zone);
}

t_zone				*get_correct_zone(t_zone *zone, size_t size)
{
	t_block		*block;

	while (zone)
	{
		if (size <= zone->avail_bytes)
		{
			block = (t_block*)((size_t)zone + S_ZONE);
			while (block)
			{
				if ((int)size <= -(block->size))
					return (zone);
				block = block->next;
			}
		}
		zone = zone->next;
	}
	return (NULL);
}

void				*add_block(t_zone **zone, int size, int min_size)
{
	t_block		*block;
	t_block		*new;

	block = (t_block*)((size_t)*zone + S_ZONE);
	while (block)
	{
		if (size <= -(block->size))
			break ;
		block = block->next;
	}
	if ((block->size + size) > -((int)S_BLOCK + min_size))
		block->size = -(block->size);
	else
	{
		new = (t_block*)((size_t)block + S_BLOCK + (size_t)size);
		new->size = (int)(block->size + (int)(S_BLOCK) + size);
		new->prev = block;
		new->next = block->next;
		block->size = size;
		block->next = new;
	}
	(*zone)->avail_bytes -= ((size_t)size + S_BLOCK);
	return ((void*)((size_t)block + S_BLOCK));
}
