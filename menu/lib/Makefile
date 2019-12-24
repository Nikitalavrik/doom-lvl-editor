#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/02 14:52:19 by tbahlai           #+#    #+#              #
#    Updated: 2018/11/02 15:00:18 by tbahlai          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = ft_lstadd.c \
		ft_power.c \
		ft_strcpy.c	\
		ft_strnequ.c \
		ft_lstdel.c	\
		ft_putchar.c \
		ft_strdel.c \
		ft_strnew.c \
		ft_lstdelone.c \
		ft_putchar_fd.c	\
		ft_strdup.c	\
		ft_strnstr.c \
		ft_atoi.c \
		ft_lstiter.c \
		ft_putendl.c \
		ft_strequ.c	\
		ft_strrchr.c \
		ft_bzero.c \
		ft_lstmap.c	\
		ft_putendl_fd.c	\
		ft_striter.c \
		ft_strsplit.c \
		ft_count_words.c \
		ft_lstnew.c \
		ft_putnbr.c	\
		ft_striteri.c \
		ft_strstr.c \
		ft_fibonacci.c \
		ft_memalloc.c \
		ft_putnbr_fd.c \
		ft_strjoin.c \
		ft_strsub.c \
		ft_isalnum.c \
		ft_memccpy.c \
		ft_putstr.c	\
		ft_strlcat.c \
		ft_strtrim.c \
		ft_isalpha.c \
		ft_memchr.c	\
		ft_putstr_fd.c \
		ft_strlen.c \
		ft_tolower.c \
		ft_isascii.c \
		ft_memcmp.c	\
		ft_sqrt.c \
		ft_strmap.c	\
		ft_toupper.c \
		ft_isdigit.c \
		ft_memcpy.c	\
		ft_strcat.c	\
		ft_strmapi.c \
		ft_isprint.c \
		ft_memdel.c	\
		ft_strchr.c	\
		ft_strncat.c \
		ft_itoa.c \
		ft_memmove.c \
		ft_strclr.c	\
		ft_strncmp.c \
		ft_len.c \
		ft_memset.c \
		ft_strcmp.c \
		ft_strncpy.c \
		ft_len_line.c \
		ft_count_line.c \
		get_next_line.c

OBJ = $(SRC:.c=.o)

CC = gcc

DEL = rm -f

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\x1b[32m -->> Compilation Success: libft.a"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(DEL) $(OBJ)

fclean: clean
	@$(DEL) $(NAME)

re: fclean all




