#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/16 13:11:08 by nlavrine          #+#    #+#              #
#    Updated: 2019/06/23 19:20:28 by nlavrine         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC_DIR = src
H_DIR = includes
OBJ_DIR = obj

SRC = 	ft_printf.c			\
		ft_floatnum.c		\
		ft_digit.c			\
		ft_check_and_p.c	\
		ft_putnbr.c			\
		ft_putstr.c			\
		ft_all_len.c		\
		ft_realloc.c		\
		ft_check.c			\
		ft_init.c			\
		ft_parse.c			\
		ft_unicode.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

LIBFT = ../libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@ar rc $@ $(OBJS) $(LIBFT)
		@ranlib $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -I $(H_DIR) -o $@ -c $< 

$(LIBFT):
	@make -C ../

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
