/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:48:28 by mkhomich          #+#    #+#             */
/*   Updated: 2020/03/01 12:47:26 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# define FPS 200
# define PI 3.141592
# define DELTA 0.5
# define FOV 60
# define THREADS 6

# define FIXP16_ROUND_UP 0x00008000
# define FIXP16_SHIFT 16
# define FIXP28_SHIFT 28
# define FIXP22_SHIFT 22
# define STEP_AN 22.5
# define MAX_PULL 15
# include <SDL2/SDL.h>
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <sys/types.h>
# include <arpa/inet.h>

typedef struct	s_cross
{
	int			x;
	int			y;
}				t_cross;

typedef struct	s_way
{
	int 		x0;
	int			y0;
	int			x1;
	int			y1;
}				t_way;

typedef struct	s_text
{
	int			*tex;
	int			w;
	int			h;
}				t_text;

typedef struct	s_inter
{
	int			dx;
	int			dudy;
	int			dvdy;
	int			dzdy;
	int			u;
	int			v;
	int			height;
	int			x;
	int			z;
}				t_inter;

typedef struct	s_toch
{
	float		x;
	float		y;
	float		z;
	float		tx1;
	float		ty1;
	float		tz1;
	float		tx2;
	float		ty2;
	float		tz2;
	int			tx;
	int			ty;
}				t_toch;

typedef struct	s_skybox
{
	SDL_Surface	*tex;
	SDL_Rect	size;
	float		kof_y;
	int			indent;
	int			count;
}				t_skybox;

typedef struct	s_point
{
	int			x;
	int			y;
	int			u;
	int			v;
	int			z;
}				t_point;

typedef struct	s_triangl
{
	t_point		t1;
	t_point		t2;
	t_point		t3;
}				t_triangl;

typedef struct	s_drtr
{
	int			xs_t;
	int			xe_t;
	int			dx;
	int			du;
	int			dz;
	int			dv;
	int			ui;
	int			vi;
	int			zi;
	int			temp_y;
	int			new_x;
}				t_drtr;

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
	double		len;
}				t_vec;

typedef struct	s_mouse
{
	int			x;
	int			y;
}				t_mouse;

typedef struct	s_tochsp
{
	t_toch		sp;
	int			nb_sp;
	int			viem;
	int			take;
	Uint32		time;
}				t_tochsp;

typedef struct  s_buttom
{
	t_mouse      st;
	int         spr;
	int         count;
	Uint32		time;
}               t_buttom;

typedef struct	s_sec
{
	int			id;
	int			*pts;
	int			color;
	int			max_toch;
	double		tex_x;
	double		tex_y;
	int			tex_h;
	int			tex_w;
	int			viem;
	int			t_full;
	int			t_win;
	int			max_but;
	t_buttom	*but;
	SDL_Rect	win;
	t_toch		**toch;
	t_tochsp	*sp;
	t_vec		v1;
	t_vec		v2;
	float		p_move;
	int			f_move;
	t_vec		move;
	int			tape;
	int			max_sp;
	int			level;
	char		bright;
	int         **tex;
	char		**l_map;
}				t_sec;

typedef struct	s_aim
{
	int			pl;
	int			zone;
	int			pull;
}				t_aim;

typedef struct	s_play
{
	double		angle_x;
	double		angle_y;
	double		speed;
	int 		id;
	int			sp;
	int			heart;
	int			armor;
	int			shot;
	int			weapons;
	int			angle_sp;
	int			count;
	int			f_move;
	int			ip;
	int			state;
	int			crouch;
	int			sec_col;
	int			buttom;
	t_toch		t;
	t_aim		aim;
	float		vec_grav;
}				t_play;

typedef struct	s_line
{
	int			x;
	int			y;
}				t_line;

typedef struct	s_lines
{
	int			delta_x;
	int			delta_y;
	int			sign_x;
	int			sign_y;
	int			error;
	int			error2;
	int			len;
}				t_lines;

typedef struct	s_move
{
	int			wsad[6];
	int			jump;
	int			run;
	int			mmap;
	int			shot;
	int 		altern;
	int         select;
}				t_move;

typedef struct	s_minimap
{
	SDL_Surface *mmap;
	int			h;
	int			w;
}				t_minimap;

typedef struct	s_sprite
{
	int			count;
	int			frame;
	t_toch		sp;
	t_text		*text;
	float		zoom;
	int			f_hud;
}				t_sprite;

typedef struct	s_level
{
	TTF_Font	*ttf;
	SDL_Color	text_color;
	int			font_size;
}				t_level;

typedef struct	s_socket
{
	struct sockaddr_in	*addr;
	struct sockaddr_in	ads;
	struct sockaddr_in	adl;
	int					*sock;
	int					skt;
	int					lstn;
	int					r;
	int					m;
	int					nb;
	int					size;
}				t_socket;

typedef struct	s_music
{
	Mix_Music	*music;
	Mix_Chunk	*shot_pistol;
}				t_music;

typedef struct	s_pull
{
	t_toch		t;
	t_vec		vec;
	int 		status;
}				t_pull;

typedef struct	s_render
{
	float		z;
	int 		sec;
}				t_render;

typedef struct	s_doom
{
	SDL_Event	event;
	SDL_Window	*window;
	SDL_Surface	*surface;
	t_sec		*sec;
	t_play		*play;
	t_skybox	skybox;
	t_mouse		mouse;
	t_toch		*toch;
	t_move		move;
	t_minimap	mmap;
	t_text		*text;
	t_sprite	*sp;
	t_music		muz;
	t_pull		pull[MAX_PULL];
	t_render	*rend;
	int			mult;
	int			count_sp;
	double		min_z;
	int			max_t;
	int			max_s;
	int			max_p;
	int			n_play;
	int			*z_buffer;
	int			count_text;
	int			*buff;
	t_level		l;
	int			nb;
	t_socket	soc;
	int			x_aim;
	int			y_aim;
	float		gravity;
	unsigned char **alpha_tab;
	int         w;
	int         h;
	int         igr_x;
	int         igr_y;
    int			aim_sec;
}				t_doom;

typedef struct	s_pth
{
	t_doom		*doom;
	t_sec		*sec;
	SDL_Rect	sq;
	int			base;
}				t_pth;

typedef struct	s_coliz
{
	float		b;
	float		c;
	float		range_min;
	int			i;
	float		y;
	int 		pl;
}				t_coliz;

typedef struct	s_light
{
    int x;
    int y;
    int r;
    char l;
}               t_light;

/*
**	Bots functions
*/

int				check_enemy(t_doom *doom, int nb);
void			bots_logic(t_doom *doom, int nb);
int				check_wall_crossing(t_doom *doom, int nb, int i);

/*
**	Another functions
*/

void			raycasting(t_doom *doom);
void			load_texture_wall (t_doom *doom);
int     		generate_alpha_tab(t_doom *doom);
void			grid_sec(t_doom *doom, t_sec *sec, char ligh);
void			rotate_y(t_doom *doom, t_toch *toch);
void			rotate_sec(t_doom *doom, t_sec *sec);
void			viem_sec_toch(t_doom *doom, t_sec *sec);
void			vector(t_toch start, t_toch end, t_vec *res);
void			put_pixel(t_doom *doom, int x, int y, int color);
int				move(t_doom *doom);
void			gen_map(t_doom *doom, int sec);
void			draw_triangl(t_doom *doom, t_triangl *tr, int *text, int tape);
void			draw_triangl_all(t_triangl *tr, t_doom *doom, int *text, int tape);
void			draw_bottom_tri(t_triangl *tr, t_doom *doom, int *text, int tape);
void			draw_top_tri(t_triangl *tr, t_doom *doom, int *text, int tape);
t_inter			interpol(t_point t1, t_point t2, int tape);
void			dx(t_inter *l, t_inter *r, t_drtr *i);
void			draw_line(t_doom *doom, t_drtr *i, int *text, int tape);
void			iter(t_inter *i);
void			render_tr2(t_doom *doom, t_sec *sec, int x, int y);
void			render_tr1(t_doom *doom, t_sec *sec, int x, int y);
int				check_viem_tr(t_doom *doom, t_triangl *tr);
int				init_full(t_doom *doom, char *str);
void			core_deg(t_doom *doom, t_toch *toch);
void			print_mmap(t_doom *doom);
int				socket_init(t_doom *doom, int flag);
float			check_h_pl(t_doom *doom, float x, float z, int pl);
int				calc_ip(unsigned char ad1, unsigned char ad2,
				unsigned char ad3, unsigned char ad4);
int				find_ip(void);
void			check_ip(t_doom *doom, int nb);
void			send_net(t_doom *doom);
void			rec_net(t_doom *doom);
int				socket_init(t_doom *doom, int flag);
void			add_play(t_doom *doom);
void			errors(int flag);
void			skybox(t_doom *doom);
void			lava(t_text *lava, t_doom *doom);
void			ani_sp(t_doom *doom, int pl);
void			init_skybox(t_doom *doom);
void			print_sprite(t_doom *doom, int p_x, int p_y, int sp, int z, int pl);
void			print_aim(t_doom *doom);
void			print_weapons(t_doom *doom);
void			print_hud(t_doom *doom);
void			print_mob(t_doom *doom);
void			z_buffsprite(SDL_Rect win, t_text *text, t_doom *doom, int z, int pl);
void			calc_uron(t_doom *doom);
void			print_sp_sec(t_doom *doom);
void			save_map(t_doom *doom, char *filename);
void			load_map(t_doom *doom, char *filename);
float			size_line(float x, float z);
void			color_grad(t_doom *doom, int color, int *col);
float			move_up(t_doom *doom, int pl);
t_vec			rot_vec(t_vec vec, float angle);
void			print_sp(t_doom *doom, int p_x, int p_y, int sp, int z, int pl);
t_coliz			coliz_pull(t_doom *doom, float x_p, float z_p, float y);
void			calc_uron_pl(t_doom *doom, int pl, int zone, int weap);
int				min_line_sec(t_doom *doom, float x, float z, t_coliz *col);
unsigned char   **burn_tab(size_t x, size_t y);
int				vec_play(t_doom *doom, int pl);

/*
** Main func
*/

void    		jump_pl(t_doom *doom, int pl, int jump);
void			game(t_doom *doom);
int     		you_win(t_doom *doom);
void			draw_text(t_doom *doom, int x, int y, char *s);
void			bzero_all(t_doom *doom);
void			vec_pull(t_doom *doom);
void			check_render(t_doom *doom);
void			add_buttom(t_doom *doom, t_sec *sec);
void			caching_tex_sec(t_doom *doom, t_sec *sec);

#endif
