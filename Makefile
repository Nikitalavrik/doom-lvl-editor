# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 15:56:05 by nlavrine          #+#    #+#              #
#    Updated: 2019/11/15 17:17:15 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = editor

SRC =	main.c			\
		error.c			\
		sys_out.c		\
		editor_init.c		\
		loop.c			\
		draw.c			\
		control.c		\
		textures.c		\
		draw_utils.c	\
		room.c			\
		dlist.c			\

CC = gcc
FLAGS = -Wall -Wextra -Werror 
SRC_DIR = srcs
H_DIR = includes
OBJ_DIR = obj
LIB = libft/libft.a
PRINTF = libft/ft_printf/libftprintf.a
GREEN = \033[0;32m

INCLUDES = 	-I./frameworks/SDL2.framework/Headers/ 			\
			-I./frameworks/SDL2_image.framework/Headers/ 	\
			-I./frameworks/SDL2_ttf.framework/Headers/ 		\
			-I./frameworks/SDL2_mixer.framework/Headers/ 	\
			-F ./frameworks


FRAMEWORKS =  	-F./frameworks 								\
    			-rpath ./frameworks 						\
    			-framework AppKit -framework OpenGL 		\
    			-framework SDL2 -framework SDL2_image 		\
    			-framework SDL2_ttf -framework SDL2_mixer	\


SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME) 

$(NAME): $(LIB) $(PRINTF) $(OBJS)
		@echo "$(GREEN)Compile $(NAME)"
		@$(CC) $(FLAGS)  -lpthread  -lm $(FRAMEWORKS) $(OBJS) $(PRINTF) $(LIB) $(PRINTF) -o $(NAME) $(INCLUDES)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(H_DIR) $(INCLUDES)

$(LIB):
	@echo "$(GREEN)Compile libft"
	@make -C ./libft/

$(PRINTF):
	@echo "$(GREEN)Compile ft_printf"
	@make -C ./libft/ft_printf/

clean:
	@echo "$(GREEN)Clear objs"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR2)
	@make -C ./libft/ clean
	@make -C ./libft/ft_printf/ clean

fclean: clean
	@echo "$(GREEN)Clear $(NAME)"
	@rm -f $(NAME)
	@make -C ./libft/ fclean
	@make -C ./libft/ft_printf/ fclean

re: fclean all