/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhomich <mkhomich@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:28:07 by mkhomich          #+#    #+#             */
/*   Updated: 2019/07/28 13:28:22 by mkhomich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void put_pixel(t_doom *doom, int x, int y, int color)
{
    int *pic;

    if (x >= 0 && x < doom->w && y >= 0 && y < doom->h && color)
    {
        pic = doom->surface->pixels + y * doom->surface->pitch + x * doom->surface->format->BytesPerPixel;
        *pic = color;
    }
}

int   viem_sec(t_doom *doom, t_sec *sec)
{
    int toch;
    int stat;

    toch = 0;
    stat = 0;
    while (toch < sec->max_toch)
    {
        if (doom->toch[sec->pts[toch]].tz2 > doom->min_z && stat == 0)
            if (toch > 0)
                return (2);
            else
                stat = 1;
        else if (doom->toch[sec->pts[toch]].tz2 <= doom->min_z && stat == 1)
            return (2);
        toch++;
    }
    if (stat == 1)
        return (1);
    return (0);
}

t_vec	rot_vec(t_vec vec, float angle)
{
	t_vec res;

	res.x = vec.x * SDL_cos(angle * PI / 180) + vec.z * SDL_sin(angle * PI / 180);
	res.y = vec.y;
	res.z = -vec.x * SDL_sin(angle * PI / 180) + vec.z * SDL_cos(angle * PI / 180);
	return (res);
}

float 	dot_prod(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.z * v2.z));
}

int	vec_play(t_doom *doom, int pl)
{
	t_vec vec;
	t_vec pl_v;
	int ang;

	vec.x = doom->play[pl].t.x - doom->play[doom->n_play].t.x;
	vec.y = 0;
	vec.z = doom->play[pl].t.z - doom->play[doom->n_play].t.z;
	vec.len = sqrt((vec.x * vec.x) + (vec.z * vec.z));
	vec.x /= vec.len;
	vec.z /= vec.len;
	pl_v = rot_vec((t_vec){0, 0, 1, 0}, 360 - doom->play[pl].angle_y + 180);
	ang = (((vec.z * pl_v.x) - (vec.x * pl_v.z)) > 0) ? 360 - ((acos(dot_prod(vec, pl_v)) * 180.0) / PI) : ((acos(dot_prod(vec, pl_v)) * 180.0) / PI);
	doom->play[pl].angle_sp = (ang + STEP_AN) / 45;
	if (doom->play[pl].angle_sp == 8)
		doom->play[pl].angle_sp = 0;
	return (ang);
}

void    raycasting(t_doom *doom)
{
    int nb;
    int	save_sec_pixel;
    int c;

    nb = 0;
    while (nb < doom->max_t)
    {
        rotate_y(doom, &doom->toch[nb]);
        nb++;
    }
    nb = 0;
    while (nb < doom->max_p)
	{
    	if (nb != doom->n_play)
		{
			rotate_y(doom, &doom->play[nb].t);
			core_deg(doom, &doom->play[nb].t);
			vec_play(doom, nb);
		}
		nb++;
	}

	nb = 0;
    doom->aim_sec = -1;
    while (nb < doom->max_s)
    {
        save_sec_pixel = doom->z_buffer[doom->y_aim * doom->surface->w + doom->x_aim];
        doom->sec[doom->rend[nb].sec].viem = viem_sec(doom, &doom->sec[doom->rend[nb].sec]);
        if (doom->sec[doom->rend[nb].sec].viem)
        {
        	if (doom->sec[doom->rend[nb].sec].f_move == 0 || (doom->sec[doom->rend[nb].sec].f_move == 1 && doom->sec[doom->rend[nb].sec].p_move >= 0 && doom->sec[doom->rend[nb].sec].p_move < 1))
			{
				rotate_sec(doom, &doom->sec[doom->rend[nb].sec]);
				viem_sec_toch(doom, &doom->sec[doom->rend[nb].sec]);
				c = 0;
				while (c < doom->sec[doom->rend[nb].sec].max_sp)
				{
					rotate_y(doom, &doom->sec[doom->rend[nb].sec].sp[c].sp);
					core_deg(doom, &doom->sec[doom->rend[nb].sec].sp[c].sp);
					c++;
				}
                if (doom->z_buffer[doom->y_aim * doom->surface->w + doom->x_aim] > save_sec_pixel)
                    doom->aim_sec = doom->rend[nb].sec;
			}
        }
        gen_map(doom, doom->rend[nb].sec);
        nb++;
    }
	if (doom->move.mmap)
		print_mmap(doom);
}