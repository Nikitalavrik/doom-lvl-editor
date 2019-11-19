/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:56:26 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/19 12:17:59 by nikita           ###   ########.fr       */
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
# define SPRITE_COLOR 0xc93706
# define SPRITE_SIZE 10
// # define STANDART_COLOR 0xc38d9e
// # define WALL_COLOR 0xe27d60
// # define TEXTURE_COLOR 0x41b3a3
// # define PRESS_WALL_COLOR 0x85dcb

/*
** flag managment
*/

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

/*
** coords in map
*/

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

/*
** same as coords, but in double, for better precision
*/

typedef struct			s_dcoords
{
	double				x;
	double				y;
	double				z;
}						t_dcoords;

/*
** point save coords
*/

typedef	struct			s_point
{
	t_coords			*coord;
	int					x;
	int					y;
	struct	s_point		*next;
	struct	s_point		*prev;
}						t_point;

/*
** line in editor, walls in doom
*/

typedef struct			s_line
{
	int					id;
	t_point				*points[2];
	int					color;
	struct s_line		*next;
	struct s_line		*prev;
}						t_line;

/*
** struct for sprite, square in editor
*/

typedef struct			s_sprite
{
	t_coords				*coord;
	int						size;
	unsigned char			alpha;
	t_dcoords				move;
	int						flag_a;
	t_coords				dist;
	t_coords				origin;
	struct	s_sprite		*next;
	struct	s_sprite		*prev;
}						t_sprite;

/*
** struct room that similiar to floor
*/

typedef struct			s_room
{
	int					id;
	t_flags				flags;
	t_point				*point;
	t_line				*lines;
	t_coords			max_xy;
	t_coords			min_xy;
	t_sprite			*sprites;
	int					area;
	unsigned char		alpha;
	struct	s_room		*next;
	struct	s_room		*prev;	
}						t_room;

/*
** main struct for SDL
*/

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

/*
** init
*/

t_editor		*init_editor(void);
void			load_textures(t_editor *editor);

/*
** drawning function
*/

void        	draw_rooms(t_editor *editor);
void			draw_lines(t_editor *editor, t_line *lines);
void			draw_cells(t_editor *editor);
void			coords_rerange(t_editor *editor);

/*
** main function
*/

int				detect_event(t_editor *editor);
int				main_loop(t_editor *editor);

/*
** pixel manipulation
*/

int				get_pixel(t_editor *editor, int x, int y);
void			put_pixel(t_editor *editor, int x, int y, int color);

/*
** double linked lists func
*/

void       	 	push_room(t_room **begin, t_point *point);
void			pop_line(t_line **begin);
void        	push_point(t_point **begin, t_coords *coord);
void       		pop_point(t_point **begin);
void        	push_line(t_line **begin, t_point *point1, t_point *point2);
void			push_sprite(t_sprite **begin, t_coords *coord);
void			pop_sprite(t_sprite **begin);

/*
** gradient
*/

int				alpha_grad(int color1, int color2, unsigned char a);
void			check_alpha(t_editor *editor);

/*
** MOUSE FUNCTION
*/

void			mouse_event(t_editor *editor, SDL_Event	event);
void			add_sprite(t_editor *editor);
void			add_line(t_editor *editor);
void			check_rooms(t_editor *editor, t_coords mouse, int type);
void			check_line(t_editor *editor, t_coords mouse);
void			mouse_move(t_editor *editor);
void			mouse_motion(t_editor *editor);
t_coords		get_coords(t_editor *editor, t_coords mouse);

/*
** KEYBOARD FUNCTION
*/

void    		close_room(t_editor *editor);
int				keyboard_events_down(t_editor *editor, SDL_Event event);
int				keyboard_events_up(t_editor *editor, SDL_Event event);

/*
** debug function 
*/

void			print_room(t_room *begin);
void			print_error(char *manage, char *message);

#endif
