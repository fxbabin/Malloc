/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_good_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:44:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 01:21:39 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			malloc_good_size(size_t size)
{
	if (size < TINY_BLOCK)
		return((size % TINY_MIN == 0) ?
			size : size - size % TINY_MIN + TINY_MIN);
	else if (size < SMALL_BLOCK)
		return((size % SMALL_MIN == 0) ?
			size : size - size % SMALL_MIN + SMALL_MIN);
	return((size % PAGE_SIZE == 0) ? size : size - size % PAGE_SIZE + PAGE_SIZE);
}

size_t			malloc_size(void *ptr)
{
	if (g_menv->curr_zone == 't' || g_menv->curr_zone == 's')
		return ((size_t)(((t_block*)((size_t)ptr - S_BLOCK))->size));
	else if (g_menv->curr_zone == 'l')
		return ((size_t)(((t_zone*)((size_t)ptr - S_ZONE))->avail_bytes));
	return (0);
}
