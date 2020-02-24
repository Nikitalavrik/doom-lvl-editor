/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:47:16 by mkhomich          #+#    #+#             */
/*   Updated: 2020/02/16 17:29:32 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void    print_mmap(t_doom *doom)
{
	SDL_Rect windowquad;

	windowquad.x = doom->w - 1 - doom->mmap.w;
	windowquad.y = 0;
	windowquad.w = doom->mmap.w;
	windowquad.h = doom->mmap.h;
	SDL_BlitSurface(doom->mmap.mmap, NULL, doom->surface, &windowquad);
}

void put_pmmap(t_doom *doom, int x, int y, int color)
{
	int *pic;

	if (x >= 0 && x < doom->mmap.w && y >= 0 && y < doom->mmap.h)
	{
		pic = doom->mmap.mmap->pixels + y * doom->mmap.mmap->pitch + x * doom->mmap.mmap->format->BytesPerPixel;
		*pic = color;
	}
}

void    dline_mmap(t_line st, t_line en, t_doom *doom, int color)
{
	t_lines l;

	l.delta_x = abs(en.x - st.x);
	l.delta_y = abs(en.y - st.y);
	l.sign_x = st.x < en.x ? 1 : -1;
	l.sign_y = st.y < en.y ? 1 : -1;
	l.error = l.delta_x - l.delta_y;
	put_pmmap(doom, doom->mmap.w / 2 + en.x, doom->mmap.h / 2 - en.y, color);
	while (st.x != en.x || st.y != en.y)
	{
		put_pmmap(doom, doom->mmap.w / 2 + st.x, doom->mmap.h / 2 - st.y, color);
		l.error2 = l.error * 2;
		if (l.error2 > -l.delta_y)
		{
			l.error -= l.delta_y;
			st.x += l.sign_x;
		}
		if (l.error2 < l.delta_x)
		{
			l.error += l.delta_x;
			st.y += l.sign_y;
		}
	}
}

void    gen_map(t_doom *doom, int sec)
{
	int nb;
	t_line st;
	t_line en;
	double zoom;

	nb = 0;
	zoom = 1;
	while (nb < doom->sec[sec].max_toch - 1)
	{
		st.x = doom->toch[doom->sec[sec].pts[nb]].tx2 * zoom;
		st.y = doom->toch[doom->sec[sec].pts[nb]].tz2 * zoom;
		en.x = doom->toch[doom->sec[sec].pts[nb + 1]].tx2 * zoom;
		en.y = doom->toch[doom->sec[sec].pts[nb + 1]].tz2 * zoom;
		dline_mmap(st, en, doom, 0xFFFFFF);
		nb++;
	}
	st.x = doom->toch[doom->sec[sec].pts[nb]].tx2 * zoom;
	st.y = doom->toch[doom->sec[sec].pts[nb]].tz2 * zoom;
	en.x = doom->toch[doom->sec[sec].pts[0]].tx2 * zoom;
	en.y = doom->toch[doom->sec[sec].pts[0]].tz2 * zoom;
	dline_mmap(st, en, doom, 0xFFFFFF);
	put_pmmap(doom, doom->mmap.w / 2, doom->mmap.h / 2, 0xFF0000);
}

float   size_line(float x, float z)
{
	return (sqrt((x * x) + (z * z)));
}

int 	check_wall_h(t_doom *doom, int h, int nb)
{
	int n;

	n = 0;
	while (n < doom->sec[nb].max_toch)
	{
		if (doom->toch[doom->sec[nb].pts[n]].y - 2 >= h)
			return (1);
		n++;
	}
	return (0);
}

int 	v_sec(t_doom *doom, float x, float z, int i)
{
	return ((doom->toch[doom->sec[i].pts[0]].x < x
	&& doom->toch[doom->sec[i].pts[3]].x > x) ||
			(doom->toch[doom->sec[i].pts[0]].x > x
			&& doom->toch[doom->sec[i].pts[3]].x < x) ||
			(doom->toch[doom->sec[i].pts[0]].z < z
			&& doom->toch[doom->sec[i].pts[3]].z > z) ||
			(doom->toch[doom->sec[i].pts[0]].z > z
			&& doom->toch[doom->sec[i].pts[3]].z < z));
}

int		min_line_sec(t_doom *doom, float x, float z, t_coliz *col)
{
	float a;
	float s;
	float p;
	float d;

	col->b = size_line(doom->toch[doom->sec[col->i].pts[0]].x - x,
				  doom->toch[doom->sec[col->i].pts[0]].z - z);
	col->c = size_line(doom->toch[doom->sec[col->i].pts[3]].x - x,
				  doom->toch[doom->sec[col->i].pts[3]].z - z);
	if (v_sec(doom, x, z, col->i) || col->pl == -2)
	{
		a = size_line(doom->toch[doom->sec[col->i].pts[0]].x -
					  doom->toch[doom->sec[col->i].pts[3]].x,
					  doom->toch[doom->sec[col->i].pts[0]].z -
					  doom->toch[doom->sec[col->i].pts[3]].z);
		p = (a + col->b + col->c) / 2;
		s = sqrt(p * (p - a) * (p - col->b) * (p - col->c));
		d = (2 * s) / a;
		if (d < col->range_min)
			if (check_wall_h(doom, col->y, col->i) || col->pl == -2)
				col->range_min = d;
	}
	else
		return (1);
	return (0);
}

float	check_colizion_pl(t_doom *doom, float x, float y, float z)
{
	t_coliz col;

	col.i = 0;
	col.range_min = 100000;
	col.y = y;
	while (col.i < doom->max_s)
	{
		if (doom->sec[col.i].tape == 1)
		{
			if (min_line_sec(doom, x, z, &col))
				if (col.b < col.range_min || col.c < col.range_min)
					col.range_min = (col.b < col.c) ? col.b : col.c;
		}
		col.i++;
	}
	return (col.range_min);
}

void   check_buttom_pl(t_doom *doom, int pl)
{
	t_coliz col;

	col.i = 0;
	col.range_min = 100000;
	col.y = doom->play[pl].t.y;
	doom->play[pl].buttom = -1;
	doom->play[pl].sec_col = -1;
	while (col.i < doom->max_s)
	{
		if (doom->sec[col.i].tape == 1)
		{
			if (min_line_sec(doom, doom->play[pl].t.x, doom->play[pl].t.z, &col))
				if (col.b < col.range_min || col.c < col.range_min)
					col.range_min = (col.b < col.c) ? col.b : col.c;
			if (col.range_min < 2 && doom->sec[col.i].max_but)
			{
				doom->play[pl].buttom = 0;
				doom->play[pl].sec_col = col.i;
			}
		}
		col.i++;
	}
}

float    coliz_pl(t_doom *doom, float x_p, float z_p, float pl)
{
	int i = 0;
	float range_min;
	float a;
	float h;

	if (pl < doom->max_p)
	{
		h = check_h_pl(doom,x_p, z_p, (int)pl);
		if (h - doom->play[(int)pl].t.y > 2)
			return (0);
	}
	range_min = check_colizion_pl(doom, x_p, doom->play[(int)pl].t.y, z_p);
	i = 0;
	while (i < doom->max_p)
	{
		if (i != pl && doom->play[i].heart)
		{
			a = size_line(doom->play[i].t.x - x_p, doom->play[i].t.z - z_p) / 1.5;
			if (a < range_min)
				range_min = a;
		}
		i++;
	}
	return (range_min);
}

t_coliz    coliz_pull(t_doom *doom, float x, float z, float y)
{
	float a;
	t_coliz col;

	col.i = 0;
	col.range_min = 100000;
	col.y = y;
	col.pl = -1;
	while (col.i < doom->max_s)
	{
		if (doom->sec[col.i].tape == 1)
			min_line_sec(doom, x, z, &col);
		col.i++;
	}
	col.i = 0;
	while (col.i < doom->max_p)
	{
		if (doom->play[col.i].heart)
		{
			a = size_line(doom->play[col.i].t.x - x,
					doom->play[col.i].t.z - z) / 1.5;
			if (a < col.range_min && y < doom->play[col.i].t.y + ((doom->play[col.i].crouch) ? 5 : 9) && y > doom->play[col.i].t.y)
			{
				col.range_min = a;
				col.pl = col.i;
			}

		}
		col.i++;
	}
	return (col);
}

float	move_up(t_doom *doom, int pl)
{
	float line_x;
	float line_z;

	line_x = coliz_pl(doom, doom->play[pl].t.x, doom->play[pl].t.z + SDL_cos(doom->play[pl].angle_y * PI / 180) * doom->play[pl].speed, pl);
	line_z = coliz_pl(doom, doom->play[pl].t.x - SDL_sin(doom->play[pl].angle_y * PI / 180) * doom->play[pl].speed, doom->play[pl].t.z, pl);
	if (line_x > 1.5)
		doom->play[pl].t.z += SDL_cos(doom->play[pl].angle_y * PI / 180) * doom->play[pl].speed;
	if (line_z > 1.5)
		doom->play[pl].t.x -= SDL_sin(doom->play[pl].angle_y * PI / 180) * doom->play[pl].speed;
	if (doom->play[pl].f_move == 0)
		doom->play[pl].f_move = 1;
	return ((line_x < line_z) ? line_x : line_z);
}

int    move(t_doom *doom)
{
	if (doom->play[doom->n_play].f_move == 1)
		doom->play[doom->n_play].f_move = 0;
	check_buttom_pl(doom, doom->n_play);
	while (SDL_PollEvent(&doom->event))
	{
		if (doom->event.type == SDL_KEYDOWN || doom->event.type == SDL_KEYUP)
		{
			if((SDL_QUIT == doom->event.type) || (SDL_KEYDOWN == doom->event.type && SDL_SCANCODE_ESCAPE == doom->event.key.keysym.scancode))
				return (0);
			else if (doom->event.key.keysym.sym == 'w')
				doom->move.wsad[0] = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == 's')
				doom->move.wsad[1] = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == 'a')
				doom->move.wsad[2] = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == 'd')
				doom->move.wsad[3] = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == 'e')
				doom->move.select = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == ' ')
				doom->move.jump = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == SDLK_LSHIFT)
				doom->move.run = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == SDLK_LCTRL)
				doom->play[doom->n_play].crouch = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == SDLK_TAB)
				doom->move.mmap = doom->event.type==SDL_KEYDOWN;
			else if (doom->event.key.keysym.sym == SDLK_1)
				doom->play[doom->n_play].weapons = 6;
			else if (doom->event.key.keysym.sym == SDLK_2)
				doom->play[doom->n_play].weapons = 7;
			else if (doom->event.key.keysym.sym == SDLK_3)
				doom->play[doom->n_play].weapons = 8;
			else if (doom->event.key.keysym.sym == SDLK_KP_1)
				doom->n_play = 0;
			else if (doom->event.key.keysym.sym == SDLK_KP_2)
				doom->n_play = 1;
			else if (doom->event.key.keysym.sym == SDLK_KP_3)
				doom->n_play = 2;
			else if (doom->event.key.keysym.sym == SDLK_KP_4)
				doom->n_play = 3;
			else if (doom->event.key.keysym.sym == SDLK_KP_6)
				doom->play[1].f_move = 0;
			else if (doom->event.key.keysym.sym == SDLK_KP_7)
				doom->play[1].f_move = 1;
			else if (doom->event.key.keysym.sym == SDLK_KP_8)
				doom->play[1].f_move = 2;
			else if (doom->event.key.keysym.sym == SDLK_KP_9)
				doom->play[1].f_move = 3;
		}
		else if (doom->event.type == SDL_MOUSEBUTTONDOWN || doom->event.type == SDL_MOUSEBUTTONUP)
		{
			if (doom->event.button.button == SDL_BUTTON_LEFT)
				doom->move.shot = doom->event.type==SDL_MOUSEBUTTONDOWN;
			if (doom->event.button.button == SDL_BUTTON_RIGHT)
				doom->move.altern = doom->event.type==SDL_MOUSEBUTTONDOWN;
		}
	}
	if (doom->move.shot && doom->play[doom->n_play].heart && doom->play[doom->n_play].f_move == 0 && doom->play[doom->n_play].shot)
	{
		if (doom->play[doom->n_play].weapons == 6 && doom->play[doom->n_play].shot)
		{
			Mix_PlayChannel( -1, doom->muz.shot_pistol, 0);
			doom->play[doom->n_play].shot--;
			doom->play[doom->n_play].f_move = 2;
		}
		else if (doom->play[doom->n_play].shot / 2)
		{
			doom->play[doom->n_play].shot -= 2;
			doom->play[doom->n_play].f_move = 2;
		}
		if (doom->play[doom->n_play].shot < 0)
			doom->play[doom->n_play].shot = 0;

	}
	else if (doom->play[doom->n_play].heart == 0)
		doom->play[doom->n_play].f_move = 3;
	if (doom->play[doom->n_play].f_move == 2 || doom->sp[doom->play[doom->n_play].weapons].count)
		if (doom->nb % ((doom->play[doom->n_play].weapons == 6) ? 4 : 2) == 0)
			doom->sp[doom->play[doom->n_play].weapons].count++;
	doom->play[doom->n_play].speed = (doom->move.run) ? (0.4) : (0.2);
	if (doom->move.wsad[0] && doom->play[doom->n_play].heart)
		move_up(doom, doom->n_play);
	if(doom->move.wsad[1] && doom->play[doom->n_play].heart)
	{
		if (coliz_pl(doom, doom->play[doom->n_play].t.x, doom->play[doom->n_play].t.z - SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed, doom->n_play) > 1.5)
		{
			doom->play[doom->n_play].t.z -= SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed;
		}
		if (coliz_pl(doom, doom->play[doom->n_play].t.x + SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed, doom->play[doom->n_play].t.z, doom->n_play) > 1.5)
		{
			doom->play[doom->n_play].t.x += SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed;
		}
		if (doom->play[doom->n_play].f_move == 0)
			doom->play[doom->n_play].f_move = 1;
	}
	if(doom->move.wsad[2] && doom->play[doom->n_play].heart)
	{
		if (coliz_pl(doom, doom->play[doom->n_play].t.x, doom->play[doom->n_play].t.z - SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed, doom->n_play) > 1.5)
		{
			doom->play[doom->n_play].t.z -= SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed;
		}
		if (coliz_pl(doom, doom->play[doom->n_play].t.x - SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed, doom->play[doom->n_play].t.z, doom->n_play) > 1.5)
		{
			doom->play[doom->n_play].t.x -= SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed;
		}
		if (doom->play[doom->n_play].f_move == 0)
			doom->play[doom->n_play].f_move = 1;
	}
	if(doom->move.wsad[3] && doom->play[doom->n_play].heart)
	{
		if (coliz_pl(doom, doom->play[doom->n_play].t.x, doom->play[doom->n_play].t.z + SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed, doom->n_play) > 1.5)
		{
			doom->play[doom->n_play].t.z += SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed;
		}
		if (coliz_pl(doom, doom->play[doom->n_play].t.x + SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed, doom->play[doom->n_play].t.z, doom->n_play) > 1.5)
		{
			doom->play[doom->n_play].t.x += SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) * doom->play[doom->n_play].speed;
		}
		if (doom->play[doom->n_play].f_move == 0)
			doom->play[doom->n_play].f_move = 1;
	}
	if (doom->move.select && doom->play[doom->n_play].heart && doom->play[doom->n_play].sec_col != -1)
	{
		doom->sec[doom->play[doom->n_play].sec_col].but[doom->play[doom->n_play].buttom].count++;
		if (doom->sec[doom->play[doom->n_play].sec_col].but[doom->play[doom->n_play].buttom].count >=
			doom->sp[doom->sec[doom->play[doom->n_play].sec_col].but[doom->play[doom->n_play].buttom].spr].frame)
			doom->sec[doom->play[doom->n_play].sec_col].but[doom->play[doom->n_play].buttom].count = 0;
		add_buttom(doom, &doom->sec[doom->play[doom->n_play].sec_col]);
		caching_tex_sec(doom, &doom->sec[doom->play[doom->n_play].sec_col]);
		doom->move.select = 0;
	}

	SDL_GetRelativeMouseState(&doom->mouse.x,&doom->mouse.y);
	doom->play[doom->n_play].angle_x += doom->mouse.y;
	doom->play[doom->n_play].angle_y -= doom->mouse.x * DELTA;
	if (doom->play[doom->n_play].angle_y >= 360.0)
		doom->play[doom->n_play].angle_y -= 360.0;
	else if (doom->play[doom->n_play].angle_y < 0)
		doom->play[doom->n_play].angle_y += 360.0;
	if (doom->play[doom->n_play].angle_x > doom->skybox.indent)
		doom->play[doom->n_play].angle_x = doom->skybox.indent;
	else if (doom->play[doom->n_play].angle_x < -doom->skybox.indent / 2)
		doom->play[doom->n_play].angle_x = -doom->skybox.indent / 2;
	return (1);
}