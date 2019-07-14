/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:50:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 17:34:13 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc_lock(void *ptr, size_t size)
{
	size_t		size_block;
	void		*new;

	if (!(size_block = malloc_size(ptr)))
		return (NULL);
	if (!(new = malloc(size)))
		return (NULL);
	ft_memcpy(new, ptr, size_block);
	free(ptr);
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

/*void		*reallocf(void *ptr, size_t size)
{
	void *new;

	pthread_mutex_lock(&g_mutex);
	new = realloc_lock(ptr, size);
	if (!new && ptr && size != 0)
		free_lock(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}*/
