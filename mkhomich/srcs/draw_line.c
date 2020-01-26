/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:54:12 by mkhomich          #+#    #+#             */
/*   Updated: 2019/12/28 19:06:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

t_inter		interpol(t_point t1, t_point t2, int tape)
{
	t_inter res;

	res.height = t2.y - t1.y;
	if (!res.height)
		printf("h = %i\n", res.height);
	res.dx = ((t2.x - t1.x) << FIXP16_SHIFT) / res.height;
	res.dudy = ((t2.u - t1.u) << ((tape) ? FIXP16_SHIFT : 0)) / res.height;
	res.dvdy = ((t2.v - t1.v) << ((tape) ? FIXP16_SHIFT : 0)) / res.height;
	res.dzdy = (t2.z - t1.z) / res.height;
	res.x = (t1.x << FIXP16_SHIFT);
	res.u = (t1.u << ((tape) ? FIXP16_SHIFT : 0));
	res.v = (t1.v << ((tape) ? FIXP16_SHIFT : 0));
	res.z = t1.z;
	return (res);
}

void		iter(t_inter *i)
{
	i->u += i->dudy;
	i->v += i->dvdy;
	i->x += i->dx;
	i->z += i->dzdy;
}

int color_grad(int color, int grad, int *col)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
	unsigned char a;
    int res;

    if (grad > 100)
        grad = 100;
    else if (grad < 5)
        grad = 5;
    a = (color >> 24);
    if (a < 255)
	{
		r = ((unsigned char)(color >> 16) * a) / 255 + ((unsigned char)(*col >> 16) * (255 - a)) / 255;
		g = ((unsigned char)(color >> 8) * a) / 255 + ((unsigned char)(*col >> 8) * (255 - a)) / 255;
		b = ((unsigned char)(color) * a) / 255 + ((unsigned char)(*col) * (255 - a)) / 255;
	}
	else
	{
		r = (color >> 16);
		g = (color >> 8);
		b = color;
	}
	res = a;
    res = ((res << 8) | ((r * grad) / 100));
    res = ((res << 8) | ((g * grad) / 100));
    res = ((res << 8) | ((b * grad) / 100));
    return (res);
}

void		draw_line(t_doom *doom, t_drtr *i, int text, int tape)
{
	int		color;
	int		nb;
	t_drtr	ib;
	int		z_buff;
	int		*tex;
	int 	w;
	int		h;

	ib = *i;
	if (!(ib.temp_y >= 0 && ib.temp_y < doom->surface->h && !((ib.xs_t < 0 &&
	ib.xe_t < 0) || (ib.xs_t > doom->surface->w && ib.xe_t > doom->surface->w))))
		return ;
	if (ib.xs_t < 0)
	{
		nb = -ib.xs_t;
		ib.xs_t = 0;
		ib.zi += (ib.dz * nb);
		ib.ui += (ib.du * nb);
		ib.vi += (ib.dv * nb);
	}
	if (ib.xe_t > doom->surface->w - 1)
		ib.xe_t = doom->surface->w - 1;
	tex = doom->text[text].tex;
	while (ib.xs_t <= ib.xe_t)
	{
		z_buff = doom->z_buffer[ib.xs_t + ib.temp_y * doom->surface->w];
		if ((z_buff == 0 || z_buff < ib.zi))
		{
			if (tape)
			{
				w =	(ib.ui >> FIXP16_SHIFT);
				h = (ib.vi >> FIXP16_SHIFT);
			}
			else if ((ib.zi >> 5))
			{
				w = ((ib.ui << 1) / (ib.zi >> 5));
				h = ((ib.vi << 1) / (ib.zi >> 5));
			}
			else
			{
				w = 0;
				h = 0;
			}
			if (w >= 0 && w < doom->text[text].w && h >= 0 && h < doom->text[text].h)
				color = tex[w + (h << 7)];
			else
				color = 0;
			if (color)
			{
				color = color_grad(color, 100, (doom->surface->pixels + ib.temp_y * doom->surface->pitch + ib.xs_t * doom->surface->format->BytesPerPixel));
				put_pixel(doom, ib.xs_t, ib.temp_y, color);
				doom->z_buffer[ib.xs_t + ib.temp_y * doom->surface->w] = ib.zi;
			}
		}
		ib.zi += ib.dz;
		ib.ui += ib.du;
		ib.vi += ib.dv;
		ib.xs_t++;
	}
	*i = ib;
}

void		dx(t_inter *l, t_inter *r, t_drtr *i)
{
	i->xs_t = ((l->x + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
	i->xe_t = ((r->x + FIXP16_ROUND_UP) >> FIXP16_SHIFT);
	i->dx = i->xe_t - i->xs_t;
	if (i->dx > 0)
	{
		i->du = (r->u - l->u) / i->dx;
		i->dv = (r->v - l->v) / i->dx;
		i->dz = (r->z - l->z) / i->dx;
	}
	else
	{
		i->du = (r->u - l->u);
		i->dv = (r->v - l->v);
		i->dz = (r->z - l->z);
	}
	i->ui = (l->u + FIXP16_ROUND_UP);
	i->vi = (l->v + FIXP16_ROUND_UP);
	i->zi = (l->z + FIXP16_ROUND_UP);
}
