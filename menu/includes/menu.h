/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:25:18 by yganzha           #+#    #+#             */
/*   Updated: 2019/12/28 16:59:51 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include <fcntl.h>
# include <SDL2/SDL.h>
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include <time.h>
# include <stdlib.h>
# include <math.h>
# include "ft_editor.h"

// typedef struct s_text
// {
//     int			*tex;
//     int			w;
//     int			h;
// }               t_text;

// typedef struct		s_play
// {
// 	double			x;
// 	double			y;
// 	double			z;
// 	double			angle_x;
// 	double			angle_y;
// 	double			speed;
// }					t_play;

typedef struct		s_toch_m
{
	double			x;
	double			y;
	double			z;
}					t_toch_m;

typedef struct		s_sec_m
{
	int				id;
	int				*pts;
	int				color;
	int				max_toch;
	int				max_port;
}					t_sec_m;

typedef struct		s_rib
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				h1;
	int				h2;
	int				k1;
	int				k2;
	int				c1;
	int				c2;
	struct s_rib	*next;
}					t_rib;

typedef struct		s_line_m
{
	int				x1;
	int				x2;
	int				xx;
	int				y1;
	int				y2;
	int				yy;
	int				f1;
	int				f2;
	t_rib			rib;
	int				delta_x;
	int				delta_y;
	int				sign_x;
	int				sign_y;
	int				error;
	int				error2;
}					t_line_m;

typedef struct		s_menu
{
	int				flag_mus; // флаг для музыки (вкл/выкл)
	int				flag_soun; // флаг звуков (вкл/выкл)
	int				flag_cont; // флаг продолжить игру
	int				f_run; // флаг запуска игры (0 - не запускать, 1 - запускать)
	int				f_diffic; // флаг уровня сложности (1 - easy, 2 - medium, 3 - hard)
	int				f_ser; //флаг если это сервер
	int				f_play; // флаг если это игрок
	int				num_play;	// количество игроков
}					t_menu;

typedef struct		s_level_m
{
	int				port;
	int				a;
	int				black;
	int				i;
	int				screen;
	int				color_btn;
	int				step;
	int				w;
	int				h;
	int				w1;
	int				h1;
	int				f_btn;
	int				font_size;
	int				flag;
	int				player;
	int				f_mult;
	int				f_numpl;
	int				anim;
	t_menu			m;
	SDL_Color		text_color;
	t_sec_m			*sec;
	SDL_Window		*win;
	SDL_Surface		*sur;
	SDL_Event		event;
	SDL_Surface		*texture[20];
	TTF_Font		*ttf;
	t_line_m			line;
	// t_play			*play;
	t_toch_m			*toch;
}					t_l;

void				start_btn(t_l *l, int fl);
int					level_edit(t_l *level);
void				print_menu(t_l *l);
void				draw_back(t_l *level);
void				draw_btn(t_l *level);
void				btn_text(t_l *l, int x, int y);
void				load_text_font(t_l *l);
void				dline(t_line a, Uint32 *p, int color, t_l *l);
void				draw_map(t_l *l);
void				draw_squar(t_l *l);
void				event(t_l *l);
void				save_touch(t_l *l);
int					ft_realloc_m(t_l *l);
void				draw_menu(t_l *l);
void				magnet_touch(t_l *l);
int					arrcp(t_sec *sec, t_sec *new_sec);
int					tochcp(t_toch *toch, t_toch *new_toch, int t);
void				reprint_map(t_l *l);
int					valid_line(double x, t_l *l);
void				send_toch(t_l *l, t_toch *toch,
					t_toch *next_toch, int color);
void				setting_btn(t_l *l, int fl);
void				get_font_size(t_l *l);
void				rewrite_font(t_l *l);
void				text_on_off(t_l *l, int x, int y, int step);
void				btn_text_s(t_l *l, int x, int y);
void				just_text(t_l *l, int flag, int step);
void				txt_back_info(t_l *l, int x, int y, int fl);
void				back_and_info(t_l *l, int flag, SDL_Rect *btn);
void				button_wind_size(t_l *l);
void				wid_and_heig(SDL_Rect *btn, t_l *l);
void				arrow_wid_and_heig(SDL_Rect *btn, t_l *l);
void				small_menu(t_l *l);
void				set_player(t_l *l);
void				save_t(t_l *l);
void				save_sec(t_l *l);
int					seccp(t_sec *sec, t_sec *new_sec);
void				multip_men(t_l *l, int fl);
void				arrow_l(t_l *l);
void				arrow_r(t_l *l);
void				on_off(t_l *l, int step);
void				init_value(t_l *l, int w, int h);
void				rewrite_font(t_l *l);
void				num_play(t_l *l, SDL_Rect *right);
void				btn_param(t_l *l, SDL_Rect *btn, int fl);
void				get_heig(t_l *l, SDL_Rect *btn);
void				choose_screen(t_l *l);
void				screen1(t_l *l);
void				add_param(t_l *l, SDL_Rect *btn, int fl);

#endif
