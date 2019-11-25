/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:56:26 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/22 17:28:27 by nlavrine         ###   ########.fr       */
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
// # include "../mkhomich/incs/doom.h"

# define NUMBER_OF_TEXTURES 9
# define E_WIDTH 1280
# define E_HEIGHT 1024
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
#define C_WIDTH 712
#define C_HEIGHT 712
#define TEXTNUM 9
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

typedef	struct			s_epoint
{
	t_coords			*coord;
	int					x;
	int					y;
	struct	s_epoint		*next;
	struct	s_epoint		*prev;
}						t_epoint;

/*
** line in editor, walls in doom
*/

typedef struct			s_eline
{
	int					id;
	t_epoint			*points[2];
	int					color;
	int					num_of_textures;
	struct s_eline		*next;
	struct s_eline		*prev;
}						t_eline;

/*
** struct for sprite, square in editor
*/

typedef struct			s_esprite
{
	t_coords				*coord;
	int						size;
	unsigned char			alpha;
	t_dcoords				move;
	int						flag_a;
	t_coords				dist;
	t_coords				origin;
	struct	s_esprite		*next;
	struct	s_esprite		*prev;
}						t_esprite;

/*
** struct room that similiar to floor
*/

typedef struct			s_room
{
	int					id;
	t_flags				flags;
	t_epoint			*point;
	t_eline				*lines;
	t_coords			max_xy;
	t_coords			min_xy;
	t_esprite			*sprites;
	int					max_sprites;
	int					area;
	unsigned char		alpha;
	struct	s_room		*next;
	struct	s_room		*prev;	
}						t_room;

/*
** struct mouse
*/

typedef struct		s_mou
{
	int				x;
	int				y;
}					t_mou;

/*
** struct coord 
*/

typedef struct		s_coord
{
	int				x;
	int				y;
	int				x1;
	int				y1;
}					t_coord;

/*
** struct new_win events
*/

typedef struct		s_ev
{
	int				m_f;
	int				up;
	int				down;
	int				r_rot;
	int				l_rot;
	int				r_move;
	int				l_move;
}					t_ev;

/*
** struct to get info from active texture
*/

typedef struct		s_act
{
	t_coord			coord;
	int				tex_num;
}					t_act;

/*
** new window to choose textures
*/

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Surface		*sur;
	Uint32			win_id;
	Uint32			**screen;
	t_mou			mouse;
	int				cam_y;
	int				delim_x;
	int				delim_y;
	t_act			active_num;
	t_ev			*events;
}					t_win;

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
	t_epoint			*point;
	t_eline				*lines;
	t_room				*selected;
	// t_doom				*doom;
	int					num_of_rooms;
	int					max_sectors;
	int					line_id;
	t_win				*new_win;
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
void			draw_lines(t_editor *editor, t_eline *lines);
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

int				get_epixel(t_editor *editor, int x, int y);
void			put_epixel(t_editor *editor, int x, int y, int color);

/*
** double linked lists func
*/

void       	 	push_room(t_room **begin, t_epoint *point);
void			pop_line(t_eline **begin);
void        	push_point(t_epoint **begin, t_coords *coord);
void       		pop_point(t_epoint **begin);
void        	push_line(t_eline **begin, t_epoint *point1, t_epoint *point2);
void			push_sprite(t_esprite **begin, t_coords *coord);
void			pop_sprite(t_esprite **begin);

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
t_room			*check_rooms(t_editor *editor, t_coords mouse, int type);
t_eline			*check_line(t_editor *editor, t_coords mouse);
t_esprite		*check_sprite(t_room *selected, t_coords mouse, double zoom);
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

/*
** doom init for editor
*/

void			d3_init(t_editor *editor);

/*
** choice textures functions
*/

void			choice_win(t_editor *editor, SDL_Event event, int flag);
void			new_event(t_editor *editor, SDL_Event event);
void			draw_rectangle(t_editor *editor);
void			draw_list_text(t_editor *editor);

#endif
