/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_good_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:44:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/11 23:14:49 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	malloc_good_size_h(size_t size, size_t bsize)
{
	size_t		ret;

	ret = ((size / bsize) * bsize) + bsize;
	if (ret < size)
		return (size);
	else if (size && size % bsize == 0)
		return (size);
	return (ret);
}

size_t			malloc_good_size(size_t size)
{
	if (size < TINY_BLOCK)
		return (malloc_good_size_h(size, TINY_MIN));
	else if (size < SMALL_BLOCK)
		return (malloc_good_size_h(size, SMALL_MIN));
	return (malloc_good_size_h(size, LARGE_MIN));
}

size_t			malloc_size(void *ptr)
{
	if (g_menv->lastzone == 't')
		return ((size_t)( ((t_tblock*)((size_t)ptr - S_TBLOCK))->size));
	else if (g_menv->lastzone == 's')
		return ((size_t)( ((t_sblock*)((size_t)ptr - S_SBLOCK))->size));
	//else if (g_menv->lastzone == 'l')
	//	return (((size_t)ptr - S_LBLOCK));
	return (0);
}
