/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:59:48 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 23:55:10 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char	*tmp;
	char	*tmp2;

	tmp = (char*)dst;
	tmp2 = (char*)src;
	while (n--)
		*(tmp++) = *(tmp2++);
	return (dst);
}

void	ft_putstr_size(char *str)
{
	int		i;
	char	buff[21];

	i = -1;
	while (++i < 20)
		buff[i] = '\0';
	i = -1;
	while (++i < 20)
	{
		buff[i] = (((str[i] >= ' ' && str[i] <= '~') || str[i] == '\0')
			? str[i] : '.');
	}
	buff[20] = '\0';
	write(1, (char*)buff, 20);
}
