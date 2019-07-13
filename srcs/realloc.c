/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:50:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 18:39:08 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
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
