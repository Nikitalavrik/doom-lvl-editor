/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:56:26 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/17 19:38:17 by nlavrine         ###   ########.fr       */
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
# define STANDART_COLOR 0xc38d9e
# define WALL_COLOR 0x5cdb95
# define TEXTURE_COLOR 0x05386b
# define PRESS_WALL_COLOR 0x85dcb
// # define STANDART_COLOR 0xc38d9e
// # define WALL_COLOR 0xe27d60
// # define TEXTURE_COLOR 0x41b3a3
// # define PRESS_WALL_COLOR 0x85dcb

typedef struct			s_dcoords
{
	double				x;
	double				y;
	double				z;
}						t_dcoords;

typedef	union			s_flags
{
	unsigned	char	flag;
	struct				s_f
	{
		unsigned char 	build 	: 1;
		unsigned char 	select 	: 1;
		unsigned char 	texture : 1;
		unsigned char 	move 	: 1;
		unsigned char	lctrl 	: 1;
		unsigned char 	hover 	: 1;
		unsigned char 	sprite 	: 1;
		unsigned char 	build7 	: 1;
	}					t_f;
}						t_flags;

typedef struct			s_coords
{
	int					x;
	int					y;
	int					z;
	int					color;
	int					r;
	int					inc;
	int					in_room;
}						t_coords;

typedef	struct			s_point
{
	t_coords			*coord;
	int					x;
	int					y;
	struct	s_point		*next;
	struct	s_point		*prev;
}						t_point;

typedef struct			s_line
{
	int					id;
	t_point				*points[2];
	int					color;
	struct s_line		*next;
	struct s_line		*prev;
}						t_line;

typedef struct			s_room
{
	int					id;
	t_flags				flags;
	t_point				*point;
	t_line				*lines;
	t_coords			max_xy;
	t_coords			min_xy;
	int					area;
	unsigned char		alpha;
	struct	s_room		*next;
	struct	s_room		*prev;	
}						t_room;

typedef	struct			s_editor
{
	TTF_Font			*font;
	SDL_Color			fg;
	SDL_Window			*win;
	SDL_Surface			*surf;
	Mix_Music			*music;
	int					width;
	int					height;
	int					mouse;
	int					line_cnt;
	t_coords			size;
	double				zoom;
	t_flags				flags;
	t_room				*rooms;
	t_coords			**coords;
	SDL_Surface			*textures[9];
	t_coords			center;
	t_coords			move_map;
	t_coords			move_save;
	t_coords			*finded;
	t_point				*point;
	t_line				*lines;
	t_room				*selected;
	int					num_of_rooms;
	int					line_id;
}						t_editor;

t_editor		*init_editor(void);

int				main_loop(t_editor *editor);


void        	draw_rooms(t_editor *editor);
void			draw_lines(t_editor *editor, t_line *lines);
void			draw_cells(t_editor *editor);
void			coords_rerange(t_editor *editor);

int				detect_event(t_editor *editor);

void			load_textures(t_editor *editor);

int				get_pixel(t_editor *editor, int x, int y);
void			put_pixel(t_editor *editor, int x, int y, int color);

void    		close_room(t_editor *editor);
void       	 	push_room(t_room **begin, t_point *point);
void			pop_line(t_line **begin);
void        	push_point(t_point **begin, t_coords *coord);
void       		pop_point(t_point **begin);
void        	push_line(t_line **begin, t_point *point1, t_point *point2);

int				alpha_grad(int color1, int color2, unsigned char a);
void			check_alpha(t_editor *editor);

void			print_error(char *manage, char *message);

#endif
