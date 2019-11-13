/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:56:26 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/13 17:29:49 by nikita           ###   ########.fr       */
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
# define MENU_WIDTH 300
# define SQUARE_SIZE 30
# define PADDING_WIDTH 20
# define PADDING_HEIGHT 20
# define STANDART_COLOR 0xbdb5b5



typedef struct	s_dcoords
{
	double		x;
	double		y;
	double		z;
}				t_dcoords;

typedef	union	s_flags
{
	unsigned	char	flag;
	struct				s_f
	{
		unsigned char build 	: 1;
		unsigned char select 	: 1;
		unsigned char texture 	: 1;
		unsigned char move 		: 1;
		unsigned char lctrl 	: 1;
		unsigned char build5 	: 1;
		unsigned char build6 	: 1;
		unsigned char build7 	: 1;
	}			t_f;
}				t_flags;

typedef struct	s_coords
{
	int			x;
	int			y;
	int			z;
	int			color;
	int			r;
	int			inc;
}				t_coords;

typedef	struct			s_point
{
	t_coords			*coord;
	struct	s_point		*next;
	struct	s_point		*prev;
}						t_point;

typedef struct			s_room
{
	t_point				*point;
	struct	s_room		*next;
	struct	s_room		*prev;	
}						t_room;

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
	t_coords	size;
	double		zoom;
	t_flags		flags;
	t_room		*rooms;
	t_coords	**coords;
	SDL_Surface	*textures[9];
	t_coords	center;
	t_coords	move_map;
	t_coords	move_save;
	t_coords	*finded;
	t_point		*point;

}				t_editor;

t_editor		*init_editor(void);

int				main_loop(t_editor *editor);

void        	draw_rooms(t_editor *editor);
void			draw_lines(t_editor *editor);
void			draw_cells(t_editor *editor);
void			coords_rerange(t_editor *editor);

int				detect_event(t_editor *editor);

void			put_pixel(t_editor *editor, int x, int y, int color);

void    		close_room(t_editor *editor);
void       	 	push_room(t_room **begin, t_point *point);
void        	push_point(t_point **begin, t_coords *coord);
void       		pop_point(t_point **begin);

void			print_error(char *manage, char *message);

#endif
