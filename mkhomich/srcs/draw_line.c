/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhomich <mkhomich@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:54:12 by mkhomich          #+#    #+#             */
/*   Updated: 2019/09/23 11:54:14 by mkhomich         ###   ########.fr       */
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

void color_grad(t_doom *doom, int color, int *col)
{
	unsigned char a;
	unsigned char b;
    int res;

    a = (color >> 24);
    if (a < 255)
	{
        res = a;
        b = 255 - a;
        res = ((res << 8) | ((doom->alpha_tab[(unsigned char)(color >> 16)][a] + doom->alpha_tab[(unsigned char)(*col >> 16)][b])));
        res = ((res << 8) | ((doom->alpha_tab[(unsigned char)(color >> 8)][a] + doom->alpha_tab[(unsigned char)(*col >> 8)][b])));
        res = ((res << 8) | ((doom->alpha_tab[(unsigned char)(color)][a] + doom->alpha_tab[(unsigned char)(*col)][b])));
        *col = res;
	}
	else
        *col = color;
}

void put_pixel_cor(int *cor, int color)
{
        *cor = color;
}

void		draw_line(t_doom *doom, t_drtr *i, int *text, int tape)
{
	int		color;
	int		nb;
	t_drtr	ib;
	int		z_buff;
	int 	w;
	int		h;
	int     *cor;
	int     count;
	int     z_b;

	ib = *i;
	if (!(ib.temp_y >= 0 && ib.temp_y < doom->h && !((ib.xs_t < 0 &&
	ib.xe_t < 0) || (ib.xs_t > doom->w && ib.xe_t > doom->w))))
		return ;
	if (ib.xs_t < 0)
	{
		nb = -ib.xs_t;
		ib.xs_t = 0;
		ib.zi += (ib.dz * nb);
		ib.ui += (ib.du * nb);
		ib.vi += (ib.dv * nb);
	}
	if (ib.xe_t > doom->w - 1)
		ib.xe_t = doom->w - 1;
    cor = (doom->surface->pixels + ib.temp_y * doom->surface->pitch + ib.xs_t * doom->surface->format->BytesPerPixel);
    count = 0;
    z_b = ib.temp_y * doom->w;
	while (ib.xs_t <= ib.xe_t)
	{
		z_buff = doom->z_buffer[ib.xs_t + z_b];
		if ((z_buff == 0 || z_buff < ib.zi))
		{
			if (tape)
			{
				w =	(ib.ui >> FIXP16_SHIFT);
				h = (ib.vi >> FIXP16_SHIFT);
			}
			else if ((ib.zi >> 5))
			{
				w = (ib.ui / (ib.zi >> 6));
				h = (ib.vi / (ib.zi >> 6));
			}
//			else
//			{
//				w = 0;
//				h = 0;
//			}
//			if (w >= 0 && w < doom->text[text].w && h >= 0 && h < doom->text[text].h)
				color = text[w + (h << 7)];
//			else
//				color = 0;
			if (color)
			{
				color_grad(doom, color, cor + count);
				doom->z_buffer[ib.xs_t + z_b] = ib.zi;
			}
		}
		ib.zi += ib.dz;
		ib.ui += ib.du;
		ib.vi += ib.dv;
		ib.xs_t++;
		count++;
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
