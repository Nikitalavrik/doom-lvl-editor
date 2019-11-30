# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 15:56:05 by nlavrine          #+#    #+#              #
#    Updated: 2019/11/29 18:10:58 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = editor

SRC =	editor_main.c		\
		error.c				\
		sys_out.c			\
		editor_init.c		\
		loop.c				\
		draw_circle.c		\
		draw_line.c			\
		draw_pixel.c		\
		draw_rooms.c		\
		control.c			\
		textures.c			\
		alpha_gradient.c	\
		room.c				\
		keyboard.c			\
		mouse.c				\
		check_mouse.c		\
		choice_win.c		\
		virtual.c			\
		free_editor.c		\
		convert_to_editor.c	\
		convert_to_doom.c	\
		choice_events.c		\
		free_doom.c			\
		coords.c			\
		room_utils.c		\
		line.c				\
		stick_to_mouse.c	\
		god_movement.c		\
		sprites.c			\
		mouse_move.c		\
		mouse_utils.c		\
		keyboard_events.c	\
		keyboard_switch.c	\
		point.c				\
		flag_managment.c	\
		choice_win_bar.c	\
		write_to_pole.c

SRC_DOOM = mkhomich/srcs/main.c \
        mkhomich/srcs/raycasting.c \
        mkhomich/srcs/sector.c \
        mkhomich/srcs/textures.c \
        mkhomich/srcs/toch.c \
       mkhomich/srcs/move.c \
        mkhomich/srcs/draw_tr.c \
        mkhomich/srcs/draw_line.c \
        mkhomich/srcs/rotate.c \
        mkhomich/srcs/render.c \
        mkhomich/srcs/init.c \
        mkhomich/srcs/set_ip.c \
        mkhomich/srcs/send_rec_net.c \
        mkhomich/srcs/init_socket.c \
        mkhomich/srcs/add_player.c \
        mkhomich/srcs/skybox.c \
        mkhomich/srcs/animation_sp_txt.c \
        mkhomich/srcs/print_sprites.c \
        mkhomich/srcs/calc_uron.c \
        mkhomich/srcs/print_sprite_sec.c \
        mkhomich/srcs/load_map.c \
        mkhomich/srcs/save_map.c \

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -Og
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
		@$(CC)  -lpthread  -lm $(FRAMEWORKS) $(OBJS) $(SRC_DOOM) $(PRINTF) $(LIB) $(PRINTF) -o $(NAME) $(INCLUDES) -fsanitize=address
	
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