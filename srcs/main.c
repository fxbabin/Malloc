/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:50:58 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/12 23:19:56 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	char	*addr;
	int		i;

	i = -1;
	while (++i < 126)
		addr = malloc(1024);
	show_alloc_mem_ex();
	return (0);
}

//#define VAL 16
#include <string.h>
#include <time.h>

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
