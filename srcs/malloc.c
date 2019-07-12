/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:43:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/12 16:47:03 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_menv				*g_menv = NULL;

static void		*ptr_allocate(size_t size)
{
	t_zone	*zone;

	zone = NULL;
	if (g_menv->curr_zone == 't')
	{
		if (g_menv->tiny == NULL && !(zonepushfront(&(g_menv->tiny), TINY_ZONE, TINY_DATA)))
			return (NULL);
		if (!(zone = get_correct_zone(g_menv->tiny, size)))
			if (!(zonepushfront(&(g_menv->tiny), TINY_ZONE, TINY_DATA)))
				return (NULL);
		if (!(zone = get_correct_zone(g_menv->tiny, size)))
			return (NULL);
		return (add_block(&zone, (int)size, TINY_MIN));
	}
	return (NULL);
}

static void		*allocate(size_t size)
{
	size_t		size_block;
	void		*ptr;

	ptr = NULL;
	size_block = malloc_good_size(size);
	if (size_block <= TINY_BLOCK)
		g_menv->curr_zone = 't';
	else if (size_block <= SMALL_BLOCK)
		g_menv->curr_zone = 's';
	else
		g_menv->curr_zone = 'l';
	if (!(ptr = ptr_allocate(size_block)))
		return (NULL);
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (g_menv == NULL && init_menv() != 0)
		return (NULL);
	if (!(ptr = allocate(size)))
		return (NULL);
	return (ptr);
}
