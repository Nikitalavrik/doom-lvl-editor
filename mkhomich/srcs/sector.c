/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhomich <mkhomich@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:34:14 by mkhomich          #+#    #+#             */
/*   Updated: 2019/09/01 17:34:15 by mkhomich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void    vector(t_toch start, t_toch end, t_vec *res)
{
	res->x = start.x - end.x;
	res->y = start.y - end.y;
	res->z = start.z - end.z;
	res->len = sqrt(res->x * res->x + res->y * res->y + res->z * res->z);
}

int		color_mix(int color, char grad)
{
	int nb;
	int res;
	unsigned char c;

	nb = 0;
	res = (color >> 24);
	while (nb < 3)
	{
		c = (unsigned char)(color >> (16 - nb * 8));
		if (c + grad > 255)
			c = 255;
		else if (c + grad < 0)
			c = 0;
		else
			c += grad;
		res = (res << 8) | c;
		nb++;
	}
	return (res);
}

void    split_tex_light(int *out, int *in, char *l, int size)
{
	int x;
	int y;


	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (out[y * size + x])
				out[y * size + x] = color_mix(out[y * size + x], l[y * size + x]);
			else
				out[y * size + x] = color_mix(in[y * size + x], l[y * size + x]);
			x++;
		}
		y++;
	}
}

void    caching_tex_sec(t_doom *doom, t_sec *sec)
{
	int x;
	int y;
	int text;

	y = 0;
	while (y < sec->tex_h)
	{
		x = 0;
		while (x < sec->tex_w)
		{
			if (!(x >= sec->win.x && x < sec->win.x + sec->win.w &&
				  y >= sec->win.y && y < sec->win.y + sec->win.h))
				text = sec->t_full;
			else
				text = sec->t_win;
			if (text)
				split_tex_light(sec->tex[y *
										 sec->tex_w + x], doom->text[text].tex, sec->l_map[y
																						   * sec->tex_w + x], doom->text[text].w);
			x++;
		}
		y++;
	}
}

void    set_light(t_sec *sec, int x, int y, char l)
{
	int x_l;
	int y_l;

	x_l = x / 128;
	y_l = y / 128;
	if (sec->l_map[y_l * sec->tex_w + x_l][(y - (128 * y_l)) * 128 + (x - (128 * x_l))] < l)
		sec->l_map[y_l * sec->tex_w + x_l][(y - (128 * y_l)) * 128 + (x - (128 * x_l))] = l;
}

void    generate_kolo(t_sec *sec, t_light *lig)
{
	int x0 = lig->x;
	int y0 = lig->y;
	int x = 0;
	int y = lig->r;
	int delta = 1 - 2 * lig->r;
	int error = 0;
	while(y >= 0) {
		set_light(sec, x0 + x, y0 + y, lig->l);
		set_light(sec, x0 + x, y0 - y, lig->l);
		set_light(sec, x0 - x, y0 + y, lig->l);
		set_light(sec, x0 - x, y0 - y, lig->l);
		set_light(sec, x0 + x + 1, y0 + y, lig->l);
		set_light(sec, x0 + x + 1, y0 - y, lig->l);
		set_light(sec, x0 - x + 1, y0 + y, lig->l);
		set_light(sec, x0 - x + 1, y0 - y, lig->l);
		error = 2 * (delta + y) - 1;
		if(delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if(delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

void    circle_generation(t_sec *sec, int x, int y, int max_r)
{
	int r;
	float l;
	float delta;
	t_light lig;

	r = 1;
	delta = ((float)120 / ((float)max_r / (float)4));
	l = -120;
	while (r < max_r / 2)
	{
		lig.x = x;
		lig.y = y;
		lig.r = r;
		lig.l = l;
		generate_kolo(sec, &lig);
		r++;
		l += delta;
	}
	while (r < max_r)
	{
		lig.x = x;
		lig.y = y;
		lig.r = r;
		lig.l = l;
		generate_kolo(sec, &lig);
		r++;
		l -= delta;
	}
}

void    lamp(t_sec * sec)
{
	int lig;

	lig = 0;
	while (lig < sec->max_sp)
	{
		if (sec->sp[lig].nb_sp == 19)
			circle_generation(sec, sec->sp[lig].sp.x * 20, sec->sp[lig].sp.z * 20, 400);
		lig++;
	}

}

void    set_pixel_sec(t_sec *sec, int x, int y, int color)
{
	int x_c;
	int y_c;

	x_c = x / 128;
	y_c = y / 128;

	if (x_c >= 0 && x_c < sec->tex_w && y_c >= 0 && y_c < sec->tex_h)
		sec->tex[y_c * sec->tex_w + x_c][(y - (128 * y_c)) * 128 + (x - (128 * x_c))] = color;

}

void    add_buttom_sec(t_doom *doom, t_sec *sec, int but)
{
	int x_t;
	int y_t;

	y_t = doom->sp[sec->but[but].spr].text[sec->but[but].count].h - 1;
	while (y_t >= 0)
	{
		x_t = 0;
		while (x_t < doom->sp[sec->but[but].spr].text[sec->but[but].count].w)
		{
			set_pixel_sec(sec, x_t + sec->but[but].st.x,
						  y_t + sec->but[but].st.y,
						  doom->sp[sec->but[but].spr].text[sec->but[but].count].tex[y_t
																					* doom->sp[sec->but[but].spr].text[sec->but[but].count].w + x_t]);
			x_t++;
		}
		y_t--;
	}
}

void    add_buttom(t_doom *doom, t_sec *sec)
{
	int nb;

	nb = 0;
	while (nb < sec->max_but)
	{
		add_buttom_sec(doom, sec, nb);
		nb++;
	}
}

void    grid_sec(t_doom *doom, t_sec *sec, char ligh)
{
	int   x;
	int   y;

	y = 0;
	vector(doom->toch[sec->pts[0]], doom->toch[sec->pts[1]], &sec->v1);
	vector(doom->toch[sec->pts[1]], doom->toch[sec->pts[2]], &sec->v2);
	sec->tex_x = (sec->v2.len * 20) / 128.0;
	sec->tex_y = (sec->v1.len * 20) / 128.0;
	sec->tex_w = (int)(sec->tex_x + 1);
	sec->tex_h = (int)(sec->tex_y + 1);
	sec->toch = (t_toch**)malloc(sizeof(t_toch*) * (int)(sec->tex_y + 2));
	sec->l_map = (char**)ft_memalloc(sizeof(char*) * sec->tex_w * sec->tex_h);
	sec->tex = (int**)ft_memalloc(sizeof(int*) * sec->tex_w * sec->tex_h);
	while (y < sec->tex_y + 1)
	{
		x = 0;
		sec->toch[y] = (t_toch*)malloc(sizeof(t_toch) * (sec->tex_x + 2));
		while (x < sec->tex_x + 1)
		{
			if (x < sec->tex_x && y < sec->tex_y)
			{
				sec->toch[y][x].x = (doom->toch[sec->pts[0]].x - (sec->v2.x * (float)x) / sec->tex_x + (-sec->v1.x * (float)y) / sec->tex_y);
				sec->toch[y][x].y = (doom->toch[sec->pts[0]].y - (sec->v2.y * (float)x) / sec->tex_x + (-sec->v1.y * (float)y) / sec->tex_y);
				sec->toch[y][x].z = (doom->toch[sec->pts[0]].z - (sec->v2.z * (float)x) / sec->tex_x + (-sec->v1.z * (float)y) / sec->tex_y);
			}
			else if (x >= sec->tex_x && y < sec->tex_y)
			{
				sec->toch[y][x].x = (doom->toch[sec->pts[0]].x - sec->v2.x + (-sec->v1.x * (float)y) / sec->tex_y);
				sec->toch[y][x].y = (doom->toch[sec->pts[0]].y - sec->v2.y + (-sec->v1.y * (float)y) / sec->tex_y);
				sec->toch[y][x].z = (doom->toch[sec->pts[0]].z - sec->v2.z + (-sec->v1.z * (float)y) / sec->tex_y);
			}
			else if (x < sec->tex_x && y >= sec->tex_y)
			{
				sec->toch[y][x].x = (doom->toch[sec->pts[0]].x - (sec->v2.x * (float)x) / sec->tex_x + -sec->v1.x);
				sec->toch[y][x].y = (doom->toch[sec->pts[0]].y - (sec->v2.y * (float)x) / sec->tex_x + -sec->v1.y);
				sec->toch[y][x].z = (doom->toch[sec->pts[0]].z - (sec->v2.z * (float)x) / sec->tex_x + -sec->v1.z);
			}
			else if (x >= sec->tex_x && y >= sec->tex_y)
			{
				sec->toch[y][x].x = (doom->toch[sec->pts[0]].x - sec->v2.x + -sec->v1.x);
				sec->toch[y][x].y = (doom->toch[sec->pts[0]].y - sec->v2.y + -sec->v1.y);
				sec->toch[y][x].z = (doom->toch[sec->pts[0]].z - sec->v2.z + -sec->v1.z);
			}
			if (!sec->tex[y * sec->tex_w + x])
			{
				sec->l_map[y * sec->tex_w + x] = (char*)ft_memalloc(sizeof(char) * 128 * 128);
				sec->tex[y * sec->tex_w + x] = (int*)ft_memalloc(sizeof(int) * 128 * 128);
				sec->l_map[y * sec->tex_w + x] = ft_memset(sec->l_map[y * sec->tex_w + x], ligh, sizeof(char) * 128 * 128);
			}
			x++;
		}
		y++;
	}
	lamp(sec);
	add_buttom(doom, sec);
	caching_tex_sec(doom, sec);
}

