# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/23 15:23:46 by mkhomich          #+#    #+#              #
#    Updated: 2020/02/17 10:29:39 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = doom-nukem

SRC =	main.c \
        raycasting.c \
        sector.c \
        textures.c \
        toch.c \
        move.c \
        draw_tr.c \
        draw_line.c \
        rotate.c \
        render.c \
        init.c \
        set_ip.c \
        send_rec_net.c \
        init_socket.c \
        add_player.c \
        skybox.c \
        animation_sp_txt.c \
        print_sprites.c \
        calc_uron.c \
        print_sprite_sec.c \
        load_map.c \
        save_map.c \
        check_enemy.c \
        cross_wall.c	\

OBJ_DIR = obj
LIB = libft/libft.a
H_DIR	= -I incs/doom.h
CC      = /usr/bin/gcc
FLAGS = -Wall -Wextra -Werror -g -O3
SRC_DIR = srcs
GREEN = \033[0;32m

TEST_MAIN = srcs/test_main.c
TEST_MAIN_O = obj/test_main.o

INCLUDES = 	-I ../frameworks/SDL2.framework/Headers/ 		\
			-I ../frameworks/SDL2_image.framework/Headers/ 	\
			-I ../frameworks/SDL2_ttf.framework/Headers/ 	\
			-I ../frameworks/SDL2_mixer.framework/Headers/ 	\
			-F ../frameworks


FRAMEWORKS =  	-F../frameworks 							\
    			-rpath ../frameworks 						\
    			-framework AppKit -framework OpenGL 		\
    			-framework SDL2 -framework SDL2_image 		\
    			-framework SDL2_ttf -framework SDL2_mixer	\

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIB) $(OBJS) $(TEST_MAIN_O)
		@echo "$(GREEN)Compile $(NAME)"
		@$(CC)  -lpthread  -lm $(FRAMEWORKS) $(OBJS) $(TEST_MAIN_O) $(LIB) -o $(NAME) $(INCLUDES) -fsanitize=address

$(TEST_MAIN_O): $(TEST_MAIN)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< $(H_DIR) $(INCLUDES)

lib: $(LIB) $(OBJS)
	@echo "$(GREEN)Compile $(NAME).a"
	@rm -f $(NAME).a
	@ar rc $(NAME).a $(OBJS)
	@ranlib $(NAME).a

$(LIB):
	@echo "$(GREEN)Compile libft"
	@make -C ../libft/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< $(H_DIR) $(INCLUDES)
		
clean:
	@echo "$(GREEN)Clear objs"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR2)
	@make -C ../libft/ clean
	@make -C ../libft/ft_printf/ clean

fclean: clean
	@echo "$(GREEN)Clear $(NAME)"
	@rm -f $(NAME)
	@rm -f $(NAME).a
	@make -C ../libft/ fclean
	@make -C ../libft/ft_printf/ fclean

re:     fclean all

.PHONY:     re all clean fclean