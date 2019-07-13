/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:52:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/13 22:40:38 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** --------------------------------- INCLUDES ---------------------------------
*/

# include <sys/mman.h>
# include <unistd.h>
# include "ft_printf.h"
# include <stdio.h>

/*
** --------------------------------- DEFINES ---------------------------------
*/

# define PAGE_SIZE		4096

# define S_BLOCK		sizeof(t_block)
# define S_ZONE			sizeof(t_zone)

# define NB_BLOCK		126

# define TINY_MIN		16
# define TINY_BLOCK		1024
# define TINY_DATA		NB_BLOCK * TINY_BLOCK
# define TINY_IZONE		S_ZONE + TINY_DATA
# define TINY_ZONE		TINY_IZONE + (PAGE_SIZE - ((TINY_IZONE) % PAGE_SIZE))

# define SMALL_MIN		512
# define SMALL_BLOCK	131072
# define SMALL_DATA		NB_BLOCK * SMALL_BLOCK
# define SMALL_IZONE	S_ZONE + SMALL_DATA
# define SMALL_ZONE		SMALL_IZONE + (PAGE_SIZE - ((SMALL_IZONE) % PAGE_SIZE))

# define LARGE_MIN		4096

/*
** ------------------------------- STRUCTURES ---------------------------------
*/

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	int				size;
	char			reserved[4];
}					t_block;

typedef struct		s_zone
{
	struct s_zone	*next;
	struct s_zone	*prev;
	size_t			avail_bytes;
}					t_zone;

typedef struct		s_menv
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
	char			curr_zone;
	char			reserved[4071];
}					t_menv;

extern t_menv		*g_menv;

/*
** ----------------------------------------------------------------------------
** -------------------------------- PROTOTYPES --------------------------------
** ----------------------------------------------------------------------------
*/

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				*calloc(size_t nmemb, size_t size);
void				*valloc(size_t size);

size_t				malloc_size(void *ptr);
size_t				malloc_good_size(size_t size);

void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);

/*
** -------------------------------- BLOCKS ------------------------------------
*/

void				*add_block(t_zone **zone, int size, int min_size);

/*
** -------------------------------- ZONES -------------------------------------
*/

void				*zonepushfront(t_zone **zone, size_t size, size_t avail);
void				*lzonepushfront(t_zone **zone, size_t size);
t_zone				*get_correct_zone(t_zone *zone, size_t size);

/*
** -------------------------------- OTHERS ------------------------------------
*/

int					init_menv(void);
void				*check_pointer(void *ptr);

/*
** ---------------------------- UTILS FUNCTIONS ------------------------------
*/

void				ft_putstr_size(char *str);
void				*ft_memcpy(void *dst, void *src, size_t n);

#endif
