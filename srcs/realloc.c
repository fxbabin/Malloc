/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:50:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 23:12:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc_lock(void *ptr, size_t size)
{
	size_t		size_block;
	void		*new;

	if (!(size_block = malloc_size(ptr)))
		return (NULL);
	if (size <= size_block)
		return (NULL);
	if (!(new = malloc_lock(size)))
		return (NULL);
	ft_memcpy(new, ptr, size_block);
	free_lock(ptr);
	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = realloc_lock(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
