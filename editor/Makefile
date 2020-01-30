# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 15:56:05 by nlavrine          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2020/01/26 16:33:53 by nlavrine         ###   ########.fr        #
=======
#    Updated: 2020/01/30 15:28:03 by nlavrine         ###   ########.fr        #
>>>>>>> 1dd0d950b9bb4a0dcb8372b0560dd10486ef666f
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
		rot_map.c			\
		choice_win_bar.c	\
		write_to_pole.c		\
		active_rectangle.c	\
		new_win_init.c		\
		editor_menu.c		\
		set_menu_flags.c	\
		save_new_win_param.c\
		set_nw_param.c		\
		free_nw.c			\
		button_nw.c			\
		rect_event.c		\
		screen_nw.c			\
		check_emenu_cursor.c\
		button_names.c		\
		init_buttons.c		\
		pole_functions.c	\
		flag_checker.c		\
		green_buttons.c		\
<<<<<<< HEAD
		ques_win.c			\
		editor_menu_events.c
=======
		editor_menu_events.c \
		os_check.c
>>>>>>> 1dd0d950b9bb4a0dcb8372b0560dd10486ef666f

SRC_DOOM = ../mkhomich/doom-nukem.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -Og
SRC_DIR = srcs
H_DIR = -I includes	\
		-I ../mkhomich/incs/
OBJ_DIR = obj
LIB = ../libft/libft.a
PRINTF = ../libft/ft_printf/libftprintf.a
GREEN = \033[0;32m

TEST_MAIN = srcs/editor_test.c
TEST_MAIN_O = obj/editor_test.o

INCLUDES = 	-I ../frameworks/SDL2.framework/Headers/ 			\
			-I ../frameworks/SDL2_image.framework/Headers/ 	\
			-I ../frameworks/SDL2_ttf.framework/Headers/ 		\
			-I ../frameworks/SDL2_mixer.framework/Headers/ 	\
			-F ../frameworks


FRAMEWORKS =  	-F../frameworks 								\
    			-rpath ../frameworks 						\
    			-framework AppKit -framework OpenGL 		\
    			-framework SDL2 -framework SDL2_image 		\
    			-framework SDL2_ttf -framework SDL2_mixer	\


SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME) 

$(NAME): $(LIB) $(PRINTF) $(OBJS) $(TEST_MAIN_O) $(SRC_DOOM)
		@echo "$(GREEN)Compile $(NAME)"
		@$(CC)  -lpthread  -lm $(FRAMEWORKS) $(OBJS) $(TEST_MAIN_O) $(SRC_DOOM) $(PRINTF) $(LIB) -o $(NAME) $(INCLUDES) #-fsanitize=address

lib: $(LIB) $(PRINTF) $(OBJS) $(SRC_DOOM)
	@echo "$(GREEN)Compile $(NAME).a"
	@rm -f $(NAME).a
	@ar rc $(NAME).a $(OBJS)
	@ranlib $(NAME).a

$(TEST_MAIN_O): $(TEST_MAIN)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< $(H_DIR) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< $(H_DIR) $(INCLUDES)

$(LIB):
	@echo "$(GREEN)Compile libft"
	@make -C ../libft/

$(SRC_DOOM):
	@make -C ../mkhomich/

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
	@rm -f $(NAME).a
	@make -C ../libft/ fclean
	@make -C ../libft/ft_printf/ fclean

re: fclean all

.PHONY:     re all clean fclean lib