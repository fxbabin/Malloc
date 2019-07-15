/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:05:44 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/15 19:14:46 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	char	*addr[4000];
	int		i;

	i = -1;
	while (++i < 300)
		addr[i] = malloc(16);
	while (--i >= 0)
		addr[i] = realloc(addr[i], 32);
	while (++i < 300)
		free(addr[i]);
	show_alloc_mem_ex();
	return (0);
}
