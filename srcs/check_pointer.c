/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:07:44 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 23:17:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*check_blockzone(t_zone *zone, void *ptr, char z)
{
	t_block		*block;

	while (zone)
	{
		block = (t_block*)((size_t)zone + S_ZONE);
		while (block)
		{
			if ((void*)((size_t)block + S_BLOCK) == ptr)
			{
				g_menv->curr_zone = z;
				return (zone);
			}
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

static void		*check_large(void *ptr)
{
	t_zone		*zone;

	zone = g_menv->large;
	while (zone)
	{
		if ((void*)((size_t)zone + S_ZONE) == ptr)
		{
			g_menv->curr_zone = 'l';
			return (zone);
		}
		zone = zone->next;
	}
	return (NULL);
}

void			*check_pointer(void *ptr)
{
	void	*ret;

	if ((ret = check_blockzone(g_menv->tiny, ptr, 't')))
		return (ret);
	else if ((ret = check_blockzone(g_menv->small, ptr, 's')))
		return (ret);
	else if ((ret = check_large(ptr)))
		return (ret);
	g_menv->curr_zone = 'z';
	return (NULL);
}
