/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:56:26 by nlavrine          #+#    #+#             */
/*   Updated: 2020/03/01 15:04:14 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FT_EDITOR_H
# define FT_EDITOR_H

# include "../../libft/libft.h"
# include "../../libft/ft_printf/include/ft_printf.h"
# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include <time.h>
# include <sys/stat.h>
# include <dirent.h>
# include "SDL_mixer.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "doom.h"

# define NUMBER_OF_TEXTURES 9
# define E_WIDTH 1024
# define E_HEIGHT 780
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
# define BACKGROUND 0xffffff
# define ACT_BACK 0x006eff
# define SPRITE_SIZE 10
# define C_WIDTH 612
# define C_HEIGHT 712
# define TEXTNUM 9
# define CONVERT_ZOOM 3
# define FLOOR_HEIGHT 20
// # define STANDART_COLOR 0xc38d9e
// # define WALL_COLOR 0xe27d60
// # define TEXTURE_COLOR 0x41b3a3
// # define PRESS_WALL_COLOR 0x85dcb

/*
** flag managment
*/

typedef	union			s_flags
{
	long				flag;
	struct				s_f
	{
		unsigned char 	build 	: 1;
		unsigned char 	select 	: 1;
		unsigned char 	texture : 1;
		unsigned char 	move 	: 1;
		unsigned char	lctrl 	: 1;
		unsigned char 	hover 	: 1;
		unsigned char 	sprite 	: 1;
		unsigned char 	visual 	: 1;
		unsigned char 	floor 	: 1;
		unsigned char 	line 	: 1;
		unsigned char	pole_1	: 1;
		unsigned char	pole_2	: 1;
		unsigned char	save_b	: 1;
		unsigned char	ret_b	: 1;
		unsigned char	rot_ax	: 1;
		unsigned char 	m_pole 	: 1;
		unsigned char	f_butt	: 1;
		unsigned char	s_butt	: 1;
		unsigned char	t_butt	: 1;
		unsigned char	d_butt	: 1;
		unsigned char	c_butt	: 1;
		unsigned char	f_floor	: 1;
		unsigned char	s_floor	: 1;
		unsigned char	t_floor	: 1;
		unsigned char	load_b	: 1;
		unsigned char	clear_b	: 1;
		unsigned char 	bselect	: 1;
		unsigned char	error	: 1;
		unsigned char	rewrite	: 1;
		unsigned char	quest	: 1;
		unsigned char	any		: 2;
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
	double				rot;
}						t_dcoords;

/*
** point save coords
*/

typedef	struct				s_epoint
{
	t_coords				*coord;
	int						x;
	int						y;
	double					rot_x;
	double					rot_y;
	struct	s_epoint		*next;
	struct	s_epoint		*prev;
}							t_epoint;

/*
** line in editor, walls in doom
*/

typedef struct			s_eline
{
	int					id;
	t_epoint			*points[4];
	int					color;
	int					num_of_textures;
	int					begin_height;
	double				height;
	int					floor;
	int					rot_angle;
	char				bright;
	int					alpha;
	struct s_eline		*next;
	struct s_eline		*prev;
}						t_eline;


/*
** struct for sprite, square in editor
*/
typedef struct			s_room t_room;

typedef struct			s_esprite
{
	t_coords				*coord;
	int						x;
	int						y;
	int						size;
	int						floor;
	unsigned char			alpha;
	t_dcoords				move;
	int						flag_a;
	t_coords				dist;
	t_coords				origin;
	int						num_of_textures;
	int						s_height;
	t_room					*room;
	struct	s_esprite		*next;
	struct	s_esprite		*prev;
}						t_esprite;

/*
** struct room that similiar to floor
*/

typedef struct			s_room
{
	int					id;
	t_epoint			*point;
	t_flags				flags;
	t_coords			max_xy;
	t_coords			min_xy;
	t_esprite			*sprites;
	int					max_mobs;
	int					max_sprites;
	int					area;
	int					height;
	int					rot_angle;
	unsigned char		alpha;
	int					f_x_angle;
	int					f_y_angle;
	int					f_height;
	int					floor;
	int					num_of_textures;
	int					del_me;
	char				bright;
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

typedef struct		s_capt
{
	char			*caption;
	int				delim;
}					t_capt;

typedef struct		s_emenu
{
	t_coord			coord;
	t_capt			caption;
	t_coord			f_cb_coord;
	t_coord			s_cb_coord;
	t_coord			t_cb_coord;
	t_coord			del_cb_coord;
	t_coord			clo_cb_coord;
	t_coord			first_floor;
	t_coord			second_floor;
	t_coord			third_floor;
	t_coord			return_butt;
	t_coord			save_butt;
	t_coord			load_butt;
	t_coord			clear_lvl;
	t_coord			select_b;
	t_coord			yes_button;
	t_coord			no_button;
	SDL_Rect		rect1;
	SDL_Rect		rect2;
}					t_emenu;

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
** param to choice window
*/

typedef struct		s_param
{
	t_eline			*line;
	t_room			*room;
	t_esprite		*sprite;
}					t_param;

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
	int				mem_space;
	t_coord			ws_coord1;
	t_coord			ws_coord2;
	t_coord			ws_coord3;
	t_coord			ws_coord4;
	t_coord			button_coord;
	char			*height_wall;
	char			*height_above;
	char			*transp;
	char			*f_height;
	void			*param;
	char			*s_height;
	int				param_flag;
	t_sprite		*editor_sprite;
	t_param			param_par;
}					t_win;

/*
** main struct for SDL
*/

typedef	struct			s_editor
{

	TTF_Font			*font;
	TTF_Font			*font1;
	SDL_Color			fg;
	SDL_Window			*win;
	SDL_Window			*ques_win;
	SDL_Surface			*surf;
	SDL_Surface			*ques_surf;
	Mix_Music			*music;
	int					width;
	int					height;
	int					mouse;
	t_coords			size;
	double				zoom;
	t_flags				flags;
	t_room				*rooms;
	t_coords			**coords;
	SDL_Surface			*textures[9];
	SDL_Surface			*button[11];
	t_coords			center;
	t_coords			move_map;
	t_coords			move_save;
	t_coords			*finded;
	t_epoint			*point;
	t_eline				*lines;
	t_room				*selected;
	int					floor;
	t_epoint			*room_point;
	int					num_of_rooms;
	int					max_sectors;
	int					line_id;
	t_win				*new_win;
	t_eline				*stick_line;
	t_room				*stick_room;
	t_epoint			*stick_point;
	float				up_down;
	float				left_right;
	t_coord				absolute_center;
	char				rot_axis;
	char				*filename;
	t_emenu				menu;
	int					param_flag;
	int					param_sflag;
	char				point_cnt;
	int					ques_flag;
	t_doom				*doom;
}						t_editor;

/*
** init
*/

int				start_editor(SDL_Window *win);

void			init_music_font(t_editor *editor);
t_editor		*init_editor(void);
void			coords_init(t_editor *editor, t_coords *size);
void			load_textures(t_editor *editor);
void			new_win_init(t_editor *editor, void *param, int flag);
void			init_emenu_buttons(t_editor *editor);

/*
** drawning function
*/

void        	draw_rooms(t_editor *editor);
void			draw_lines(t_editor *editor, t_eline *lines);
void			draw_cells(t_editor *editor);
void			draw_stick_line(t_editor *editor);
void			draw_stick_room(t_editor *editor);
void			coords_rerange(t_editor *editor);
void			draw_editor_menu(t_editor *editor);
void			draw_caption(t_editor *editor, t_coord coord,\
				SDL_Window *win, t_capt caption);

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

void			mouse_button_down(t_editor *editor);
void			mouse_zoom(t_editor *editor, SDL_Event	event);
void			add_sprite(t_editor *editor);
void			add_line(t_editor *editor);
t_room			*check_rooms(t_editor *editor, t_coords mouse, int type);
t_eline			*check_line(t_editor *editor, t_coords mouse);
t_esprite		*check_sprite(t_room *selected, t_coords mouse, double zoom);
t_coords		*check_point(t_editor *editor, t_coords mouse_position);
void			mouse_move(t_editor *editor);
void			mouse_motion(t_editor *editor);
t_coords		get_coords(t_editor *editor, t_coords mouse);
void			delete_line(t_editor *editor, t_eline *line);
double			calc_short_dist(t_eline *line, t_coords mouse);
int				editor_menu_events(t_editor *editor,\
				t_coords mouse_position, SDL_Event event);

/*
** KEYBOARD FUNCTION
*/

void    		close_room(t_editor *editor);
int				keyboard_events_down(t_editor *editor, SDL_Event event);
int				keyboard_events_up(t_editor *editor, SDL_Event event);
void			switch_to_select(t_editor *editor);
void			switch_to_floor_build(t_editor *editor);
void			switch_to_visual_3d(t_editor *editor);
void			switch_to_line_build(t_editor *editor);
void			delete_prev(t_editor *editor);
void			find_and_delete(t_editor *editor);
void			delete_sprite(t_editor *editor, t_esprite *sprite);
void			switch_to_sprite_put(t_editor *editor);
void			clear_level(t_editor *editor);

/*
** debug function 
*/

void			print_room(t_room *begin);
void			print_error(char *manage, char *message);
void			draw_error_mess(t_editor *editor);

/*
** doom init for editor
*/

void			d3_init(t_editor *editor);
void			convert_doom_to_editor(t_editor *editor, t_doom *doom);
void			convert_rooms(t_editor *editor);
void			load_to_editor(t_editor *editor, char *filename);

/*
** screen new win functions
*/

void			put_text_to_screen(t_editor *editor, int y, int x, int *k);
void			ft_clear_new_screen(t_editor *editor);
void			add_sprites_to_screen(t_editor *editor);
void			add_textures_to_screen(t_editor *editor);

/*
** choice textures functions
*/

void			choice_win(t_editor *editor, SDL_Event event, int flag, void *param);
void			new_event(t_editor *editor, SDL_Event event);
void			draw_rectangle(t_editor *editor);
void			draw_list_text(t_editor *editor);
void 			add_text_to_space(t_editor *editor, t_coord coord,\
				SDL_Window *win, char *text);
void			draw_white_space(t_coord coord, SDL_Surface *surf, Uint32 color);
void			draw_right_menu(t_editor *editor);
t_coord			get_input_coord(int x, int y);
void			get_pole_num(t_editor *editor);
void			write_to_pole(t_editor *editor, char **text, SDL_Event event);
t_coord			get_coord_from_flag(t_editor *editor);
void			draw_button(t_editor *editor, int button_num);
void			draw_first_rectangle(t_editor *editor);
void			put_to_screen(t_editor *editor, int x, int y, Uint32 collor);
void			write_text_to_pole(t_editor *editor);
void			write_to_first_pole(t_editor *editor);
void			write_to_second_pole(t_editor *editor);
void			write_to_third_pole(t_editor *editor);
void			rewrite_text_to_pole(t_editor *editor);
t_text   		convert_tex(SDL_Surface *dst, int w, int h);
void			save_parametrs(t_editor *editor);
void			set_nw_param(t_editor *editor, SDL_Event event);
void			close_choice_win(t_editor *editor);
void			set_new_win_button_texture(t_editor *editor, SDL_Event event);
int				check_currsor(t_editor *editor);
void			get_nw_act_pole(t_editor *editor);
void			load_correct_scale_sprite(t_editor *editor);

/*
** menu flags
*/

void			check_emenu_cursor(t_editor *editor, t_coords mouse_position);
int				check_emenu_scursor(t_editor *editor, t_coords mouse_position);
void			null_buttons(t_editor *editor);
int				check_position(t_coords mouse_position, t_coord coord);

/*
** ques functions
*/

int				ques_win(t_editor *editor, SDL_Event event);
void			ques_event(t_editor *editor, SDL_Event event,\
				t_coords mouse_position);
void			ques_button_names(t_editor *editor);

/*
** Buttons function
*/

void			write_button_name(t_editor *editor);
void			editor_autosave(t_editor *editor);
void			init_emenu_buttons(t_editor *editor);
void			draw_emenu_big_buttons(t_editor *editor);
void			draw_emenu_help_buttons(t_editor *editor);
/*
** FREE
*/

void			free_doom(t_doom *doom);
void			partly_free_editor(t_editor *editor);
void			free_lines(t_eline **line);
void			free_sprites(t_esprite **sprites);
void			free_rooms(t_room **room);
void			free_points(t_epoint **point);
void			free_sec(t_sec *sec);


/*
** room func
*/

void			sort_rooms(t_room **rooms, int len);
void			calc_max_min(t_room *room);
void			add_room(t_editor *editor);
void       	 	push_room(t_room **begin, t_epoint *point);
void			pop_room(t_room **begin);
void			delete_room(t_editor *editor, t_room *room);
t_room			*find_room_by_id(t_editor *editor, int id);

/*
** line func
*/

t_eline			*find_line_by_id(t_editor *editor, int id);

/*
** stick line and room func
*/

void			stick_line(t_editor *editor);
void			delete_stick_line_room(t_editor *editor);
void			stick_room(t_editor *editor);
void			delete_stick_point(t_editor *editor);

/*
** god movement
*/

void			god_rot_move(t_editor *editor, SDL_Event event);

/*
** FLAG MANAGE
*/

void			null_editing_flags(t_flags *flags);
void			set_emenu_flag(t_editor *editor, SDL_Event event);
void			set_to_zero_emenu_flags(t_editor *editor);
void			check_emenu_pole(t_editor *editor);

/*
** rotating map
*/

void			change_view(t_editor *editor);

/*
**	os check
*/

int				check_file_in_dir(char *filename);

#endif
