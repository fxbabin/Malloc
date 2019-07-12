# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/17 15:40:11 by fbabin            #+#    #+#              #
#    Updated: 2019/07/13 01:24:05 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -Weverything

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TEST			=	a.out
NAME			=	libft_malloc_$(HOSTTYPE).so
LINK			=	libft_malloc.so
_SRCS			=	malloc.c zones.c show_alloc_mem.c show_alloc_mem_ex.c \
					malloc_good_size.c utils.c check_pointer.c large_zones.c \
					free.c
					#ree_large.c \
					free.c utils.c show_alloc_mem.c realloc.c check_pointer.c
_SRCS_TEST		=	main.c

SRCS_DIR		=	srcs
SRCS			=	$(addprefix $(SRCS_DIR)/,$(_SRCS))

OBJS_DIR		=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/,$(_SRCS:%.c=%.o))
OBJS_TEST		=	$(addprefix $(OBJS_DIR)/,$(_SRCS_TEST:%.c=%.o))

INCS_DIR		=	includes
INCS			=	-I $(INCS_DIR) -I $(LIB_DIR)/includes
HEADER			=	$(INCS_DIR)/malloc.h

LIB_DIR			=	ft_printf
_LIBFT			=	libftprintf.a
LIBFT			=	$(LIB_DIR)/$(_LIBFT) 


all: lib $(HEADER) $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
		@$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L$(LIB_DIR) -lftprintf -shared $(OBJS)
			ln -sf $(NAME) $(LINK)
		@echo "$(NAME) : Done"

$(OBJS_DIR):
		@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
		$(CC) $(CFLAGS) -fPIC $(INCS) -c -o $@ $<

lib:
	@make -C $(LIB_DIR)

test: lib $(HEADER) $(TEST)
	
$(TEST): $(OBJS_DIR) $(OBJS) $(OBJS_TEST)
		@$(CC) $(CFLAGS) -o $(TEST) -L$(LIB_DIR) -lftprintf $(OBJS) $(OBJS_TEST) $(INCS)
		@echo "test compilation : Done"

re_test:
		@make fclean
		@make test

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -rf $(OBJS_DIR)
		@echo "$(NAME) clean : Done"

fclean: clean
		@/bin/rm -f $(NAME) $(LINK) a.out
		@echo "$(NAME) fclean : Done"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
