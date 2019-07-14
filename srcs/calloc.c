/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:59:30 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 23:08:59 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;

	tmp = (char*)b;
	while (len--)
		*(tmp++) = (char)c;
	return (b);
}

static void		*calloc_lock(size_t count, size_t size)
{
	void	*ptr;

	if (!(ptr = malloc_lock(count * size)))
		return (NULL);
	ft_memset(ptr, 0, malloc_good_size(count * size));
	return (ptr);
}

void			*calloc(size_t count, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = calloc_lock(count, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
