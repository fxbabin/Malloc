/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:05:44 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/15 20:44:00 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	void *ptr;

	ptr = malloc(992);
	ptr = malloc(1024);
	ptr = malloc(1024 * 32);
	ptr = malloc(1024 * 1024);
	ptr = malloc(1024 * 1024 * 16);
	ptr = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
