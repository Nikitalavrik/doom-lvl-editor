# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 13:28:00 by yganzha           #+#    #+#              #
#    Updated: 2019/12/28 17:37:26 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = doom

SRC     = main.c \
		level_edit.c \
		buttons.c \
		settings.c \
		start_game.c \
		sett_txt.c \
		sett_sizes.c \
		menu_multipl.c \
		menu_mult_1.c \
		params_btn.c \
		screens.c \
		events.c

NAME = menu


LIB_DOOM = ../mkhomich/doom-nukem.a
LIB_EDITOR = ../editor/editor.a
H_DOOM = -I ../mkhomich/incs
H_EDITOR = -I ../editor/includes/

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -Og
SRC_DIR = src
H_DIR = includes

OBJ_DIR = obj
LIB = ../libft/libft.a
PRINTF = ../libft/ft_printf/libftprintf.a
GREEN = \033[0;32m

INCLUDES = 	-I ../frameworks/SDL2.framework/Headers/ 			\
			-I ../frameworks/SDL2_image.framework/Headers/ 	\
			-I ../frameworks/SDL2_ttf.framework/Headers/ 		\
			-I ../frameworks/SDL2_mixer.framework/Headers/ 	\
			-F ../frameworks


FRAMEWORKS =  	-F ../frameworks 								\
    			-rpath ../frameworks 						\
    			-framework AppKit -framework OpenGL 		\
    			-framework SDL2 -framework SDL2_image 		\
    			-framework SDL2_ttf -framework SDL2_mixer	\


SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME) 

$(NAME): $(LIB) $(PRINTF) $(OBJS)
		@echo "$(GREEN)Compile $(NAME)"
		$(CC)  -lpthread  -lm $(FRAMEWORKS) $(OBJS) $(LIB_DOOM) $(LIB_EDITOR) $(PRINTF) $(LIB) -o $(NAME) $(INCLUDES) $(H_DOOM) $(H_EDITOR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(H_DIR) $(H_EDITOR) $(H_DOOM) $(INCLUDES) 

$(LIB):
	@echo "$(GREEN)Compile libft"
	@make -C ../libft/

$(PRINTF):
	@echo "$(GREEN)Compile ft_printf"
	@make -C ../libft/ft_printf/

clean:
	@echo "$(GREEN)Clear objs"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR2)
	@make -C ../libft/ clean
	@make -C ../libft/ft_printf/ clean

fclean: clean
	@echo "$(GREEN)Clear $(NAME)"
	@rm -f $(NAME)
	@make -C ../libft/ fclean
	@make -C ../libft/ft_printf/ fclean

re: fclean all