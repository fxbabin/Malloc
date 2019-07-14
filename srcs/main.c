/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:50:58 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/14 21:41:00 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	char	*addr[1000];
	int		i;

	i = -1;
	while (++i < 300)
		addr[i] = malloc_lock(16);
	i = -1;
	while (++i < 300)
	{
		//free(addr[i]);
		//ft_printf("%d\n", i);
		/*if (i == 117)
		{
			show_alloc_mem_ex();
			ft_printf("%p\n", addr[i]);
		}*/
		addr[i] = realloc_lock(addr[i], 1024);
		//if (i == 26)
		//	break;
	}
	while (--i >= 0)
		free(addr[i]);
	addr[0] = malloc(1024);
	addr[1] = malloc(1024);
	addr[2] = malloc(1024);
	addr[3] = malloc(1024);
	addr[4] = malloc(1024);
	addr[5] = malloc(1024);
	addr[6] = malloc(1024);
	addr[7] = malloc(1024);
	addr[8] = malloc(1024);
	addr[9] = malloc(1024);
	ft_printf("%p\n", ((t_block*)((size_t)addr[9] - S_BLOCK))->prev);
	//free(addr[9]);
	show_alloc_mem_ex();
	/**/
	/*show_alloc_mem_ex();
	//i = -1;
	while (--i >= 0)
		free(addr[i]);*/
	//show_alloc_mem_ex();
	//ft_printf("%p || %c\n", check_pointer(addr[54]), g_menv->curr_zone);
	return (0);
}

//#define VAL 1p
//#include <string.h>
//#include <time.h>

/*static void free_fbabin(char *str[44000])
{
	int tab[VAL];
	int index;
	
	index = -1;
	while (++index < VAL)
		tab[index] = -1;
	while (1)
	{
		index = rand() % VAL;
		if (tab[index] != 0) {
			free(str[index]);
			tab[index] = 0;
		}
		int i;

		i = 0;
		for (i = 0; i < VAL; i++) {
			if (tab[i] != 0) {
				break ;
			}
		}
		if (i == VAL) {
			show_alloc_mem();
			return ;
		}
	}
}

static void toto(void)
{
	int			i;
	char		*str[44000];

	srand(time(NULL));
	i = -1;
	while (++i < VAL)
	{
		
		str[i] = malloc(131072);
	}
		//show_alloc_mem();
	//show_alloc_mem_ex();
	i = -1;
	free_fbabin(str);
}*/

/*int		main(void)
{
	ft_printf("%d\n", TINY_ZONE);
	ft_printf("%d\n", SMALL_ZONE);
	return (0);
}*/
