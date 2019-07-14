/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:43:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 23:11:30 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_menv				*g_menv = NULL;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void		*allocate_blockzone(t_zone *zone, size_t size)
{
	if (g_menv->curr_zone == 't')
	{
		if (g_menv->tiny == NULL
			&& !(zonepushfront(&(g_menv->tiny), TINY_ZONE, TINY_DATA)))
			return (NULL);
		if (!(zone = get_correct_zone(g_menv->tiny, size)))
			if (!(zonepushfront(&(g_menv->tiny), TINY_ZONE, TINY_DATA)))
				return (NULL);
		if (!(zone = get_correct_zone(g_menv->tiny, size)))
			return (NULL);
		return (add_block(&zone, (int)size, TINY_MIN));
	}
	if (g_menv->curr_zone == 's')
	{
		if (g_menv->small == NULL
			&& !(zonepushfront(&(g_menv->small), SMALL_ZONE, SMALL_DATA)))
			return (NULL);
		if (!(zone = get_correct_zone(g_menv->small, size)))
			if (!(zonepushfront(&(g_menv->small), SMALL_ZONE, SMALL_DATA)))
				return (NULL);
		if (!(zone = get_correct_zone(g_menv->small, size)))
			return (NULL);
		return (add_block(&zone, (int)size, SMALL_MIN));
	}
	return (NULL);
}

static void		*ptr_allocate(size_t size)
{
	t_zone	*zone;
	void	*ptr;

	ptr = NULL;
	zone = NULL;
	if ((ptr = allocate_blockzone(NULL, size)))
		return (ptr);
	if (g_menv->curr_zone == 'l')
	{
		if (!(zone = lzonepushfront(&(g_menv->large), size)))
			return (NULL);
		return ((void*)((size_t)zone + S_ZONE));
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

void			*malloc_lock(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (g_menv == NULL && init_menv() == -1)
		return (NULL);
	if (!(ptr = allocate(size)))
		return (NULL);
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;
	
	pthread_mutex_lock(&g_mutex);
	ptr = malloc_lock(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
