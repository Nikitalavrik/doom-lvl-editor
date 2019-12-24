#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yganzha <yganzha@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 13:28:00 by yganzha           #+#    #+#              #
#    Updated: 2019/06/13 13:28:01 by yganzha          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME    = doom

SRC     = src/main.c \
		src/level_edit.c \
		src/buttons.c \
		src/settings.c \
		src/start_game.c \
		src/sett_txt.c \
		src/sett_sizes.c \
		src/menu_multipl.c \
		src/menu_mult_1.c \
		src/params_btn.c \
		src/screens.c \
		src/events.c

OUT     = $(SRC:.c=.o)

LIBFT   = lib/

HDR		= includes/doom.h

CC      = /usr/bin/gcc

CFLAGS  = -Wall -Wextra -g # -fsanitize=address  -Werror

SDL_HEADER = -I ./frameworks/SDL2.framework/A/Headers/ \
    -I ./frameworks/SDL2_ttf.framework/Versions/A/Headers/ \
    -I ./frameworks/SDL2_image.framework/Versions/A/Headers/ \
    -I ./frameworks/SDL2_mixer.framework/Headers/ \
 	-F ./frameworks/

SDL_FLAGS = -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf

SDL2_P = -rpath ./frameworks/

all:        $(NAME)
$(NAME):    $(OUT) $(LIBFT)
	@make -C $(LIBFT)	
	@$(CC) $(CFLAGS) -L $(LIBFT) -lft $(SDL_HEADER) $(SDL2_P) $(SDL_FLAGS) $(OUT) -o $(NAME) -I $(HDR) 

%.o : %.c $(HDR) $(LIBFT)
	@$(CC) $(CFLAGS) $(SDL_HEADER) -o $@ -c $< -I .

clean:
	@make fclean -C $(LIBFT)
	@rm -f $(OUT)

fclean:     clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)

re:     fclean all
	
.PHONY:     re all clean fclean
