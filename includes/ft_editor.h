/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:56:26 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 16:45:27 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FT_EDITOR_H
# define FT_EDITOR_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <pthread.h>
# include "../libft/ft_printf/include/ft_printf.h"
# include <math.h>
# include <time.h>
# include "SDL_mixer.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"

# define NUMBER_OF_TEXTURES 9
# define WIDTH 1280
# define HEIGHT 720
# define WALL_HEIGHT HEIGHT

typedef struct	s_dcoords
{
	double		x;
	double		y;
	double		z;
}				t_dcoords;

typedef struct	s_coords
{
	int			x;
	int			y;
	int			z;
	int			texture;
	int			prev_z;
}				t_coords;

typedef	struct	s_editor
{
	TTF_Font	*font;
	SDL_Color	fg;
	SDL_Window	*win;
	SDL_Surface	*surf;
	Mix_Music	*music;
	int			width;
	int			height;
	int			mouse;
	t_coords	**coords;
	SDL_Surface	*textures[9];
}				t_editor;

t_editor		*init_editor(void);

int				main_loop(t_editor *editor);

int				detect_event(t_editor *editor);

void			print_error(char *manage, char *message);

#endif
