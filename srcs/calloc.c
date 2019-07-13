/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:59:30 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 22:41:53 by fbabin           ###   ########.fr       */
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

void			*calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(count * size)))
		return (NULL);
	ft_memset(ptr, 0, malloc_good_size(count * size));
	return (ptr);
}
