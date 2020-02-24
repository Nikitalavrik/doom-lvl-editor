/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:42:17 by mkhomich          #+#    #+#             */
/*   Updated: 2020/02/16 17:17:21 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	bzero_all(t_doom *doom)
{
	bzero(doom->z_buffer, sizeof(int) * doom->w * doom->h);
	bzero(doom->mmap.mmap->pixels, sizeof(int) * doom->mmap.w * doom->mmap.h);
}

void	z_buffsprite(SDL_Rect win, t_text *text, t_doom *doom, int z, int pl)
{
	int x;
	int y;
	int buf;
	int step_x;
	int step_y;

	y = 0;
	if (!win.w || !win.h)
		return ;
	step_x = (text->w << FIXP16_SHIFT) / win.w;
	step_y = ((text->h << FIXP16_SHIFT) / win.h);
	while (y < win.h)
	{
		x = 0;
		while (x < win.w)
		{
			if (x + win.x >= 0 && x + win.x < doom->w && y + win.y >= 0 && y + win.y < doom->h)
			{
				buf = text->tex[((y * step_y) >> FIXP16_SHIFT) * text->w + ((x * step_x) >> FIXP16_SHIFT)];
				if (buf)
				{
					if (z > 0)
					{
						if (doom->z_buffer[x + win.x + (y + win.y) * doom->w] < z || doom->z_buffer[x + win.x + (y + win.y) * doom->w] == 0)
						{
							if (x + win.x == doom->x_aim && y + win.y == doom->y_aim && pl - 1 != doom->n_play && pl)
							{
								doom->play[doom->n_play].aim.pl = pl - 1;
								doom->play[doom->n_play].aim.zone = ((y * 4) / win.h) + 1;
							}
							doom->z_buffer[x + win.x + (y + win.y) * doom->w] = z;
							put_pixel(doom, x + win.x, y + win.y, buf);
						}
					}
					else
						put_pixel(doom, x + win.x, y + win.y, buf);
				}

			}
			x++;
		}
		y++;
	}
}

void	print_sprite(t_doom *doom, int p_x, int p_y, int sp, int z, int pl)
{
	SDL_Rect win;

	if (doom->sp[sp].count > doom->sp[sp].frame - 1)
		doom->sp[sp].count = 0;
	win.x = p_x - ((int)(doom->sp[sp].text[doom->sp[sp].count].w * doom->sp[sp].zoom) >> 1);
	win.y = p_y - ((int)(doom->sp[sp].text[doom->sp[sp].count].h * doom->sp[sp].zoom) >> ((sp == 9 && doom->play[pl].crouch) ? 1 : 0));
	win.w = (int)(doom->sp[sp].text[doom->sp[sp].count].w * doom->sp[sp].zoom);
	win.h = ((int)(doom->sp[sp].text[doom->sp[sp].count].h * doom->sp[sp].zoom) >> ((sp == 9 && doom->play[pl].crouch) ? 1 : 0));
	if (z == 0 && sp != 9 && sp != 10 && sp != 11)
		z_buffsprite(win, &doom->sp[sp].text[doom->sp[sp].count], doom, z, pl);
	else if (doom->play[pl].angle_sp != 0 &&  doom->play[pl].angle_sp < 28)
		z_buffsprite(win, &doom->sp[sp].text[doom->play[pl].count + (32 - (4 * doom->play[pl].angle_sp))], doom, z, pl + 1);
	else if (doom->play[pl].count + doom->play[pl].angle_sp < doom->sp[sp].frame)
		z_buffsprite(win, &doom->sp[sp].text[doom->play[pl].count + doom->play[pl].angle_sp], doom, z, pl + 1);
}


void	draw_text(t_doom *doom, int x, int y, char *s)
{
	SDL_Surface *message;
	SDL_Rect f;

	f.x = x;
	f.y = y;
	doom->l.text_color = (SDL_Color){80, 10, 10, 0};
	message = TTF_RenderText_Solid(doom->l.ttf, s, doom->l.text_color);
	SDL_BlitSurface(message, NULL, doom->surface, &f);
	SDL_FreeSurface(message);
}

int pnpoly(t_doom *doom, int sec, float x, float y)
{
    int c = 0;
    t_sec temp;

    temp = doom->sec[sec];
    for (int i = 0, j = temp.max_toch - 1; i < temp.max_toch; j = i++)
    {
        if (((doom->toch[temp.pts[i]].z < doom->toch[temp.pts[j]].z) &&
             (doom->toch[temp.pts[i]].z <= y) && (y <= doom->toch[temp.pts[j]].z)
             && ((doom->toch[temp.pts[j]].z - doom->toch[temp.pts[i]].z) *
                 (x - doom->toch[temp.pts[i]].x) >
                 (doom->toch[temp.pts[j]].x - doom->toch[temp.pts[i]].x) *
                 (y - doom->toch[temp.pts[i]].z))) || ((doom->toch[temp.pts[i]].z
                                                        > doom->toch[temp.pts[j]].z) && (doom->toch[temp.pts[j]].z <= y)
                                                       && (y <= doom->toch[temp.pts[i]].z) && ((doom->toch[temp.pts[j]].z
                                                                                                - doom->toch[temp.pts[i]].z) * (x - doom->toch[temp.pts[i]].x) <
                                                                                               (doom->toch[temp.pts[j]].x - doom->toch[temp.pts[i]].x) *
                                                                                               (y - doom->toch[temp.pts[i]].z))))
            c = !c;
    }
    return c;
}

float cal_h_pl(t_doom *doom, int sec, float x, float z)
{
    float cof;
    float res;

    res = 0;
    cof = ((doom->toch[doom->sec[sec].pts[0]].x - x) / doom->sec[sec].v1.x);
    if (cof <= 1 && cof >= 0)
        res += doom->toch[doom->sec[sec].pts[0]].y - (doom->sec[sec].v1.y * cof);
    else
    {
        cof = ((doom->toch[doom->sec[sec].pts[0]].z - z) / doom->sec[sec].v1.z);
        if (cof <= 1 && cof >= 0)
            res += doom->toch[doom->sec[sec].pts[0]].y - (doom->sec[sec].v1.y * cof);
    }
    cof = ((doom->toch[doom->sec[sec].pts[1]].x - x) / doom->sec[sec].v2.x);
    if (cof <= 1 && cof >= 0)
        res -= doom->sec[sec].v2.y * cof;
    else
    {
        cof = ((doom->toch[doom->sec[sec].pts[1]].z - z) / doom->sec[sec].v2.z);
        if (cof <= 1 && cof >= 0)
            res -= doom->sec[sec].v2.y * cof;
    }
    return (res);
}

float check_h_pl(t_doom *doom, float x, float z, int pl)
{
    int sec;
    float h;
    float buf;

    sec = 0;
    h = -1000;
    while (sec < doom->max_s && doom->play[pl].heart != 0)
    {
        if (doom->sec[sec].tape == 0)
            if (pnpoly(doom, sec, x, z) % 2)
            {
                buf = cal_h_pl(doom, sec, x, z);
                if (h < buf && (buf - doom->play[pl].t.y < 10 && buf - doom->play[pl].t.y > -1))
                    h = buf;
            }
        sec++;
    }
    return (h);
}

void    jump_pl(t_doom *doom, int pl, int jump)
{
    float h;

    if ((jump || (doom->move.jump && pl == doom->n_play)) && doom->play[pl].state == 0)
    {
        doom->play[pl].state = 1;
        doom->play[pl].vec_grav = 0.92;
    }
    h = check_h_pl(doom, doom->play[pl].t.x, doom->play[pl].t.z, pl);
    if (h - doom->play[pl].t.y < 0.5 && h - doom->play[pl].t.y > 0 && doom->play[pl].state == 0)
        doom->play[pl].t.y = h;
    else if (doom->play[pl].state == 0 && h < doom->play[pl].t.y)
    {
        doom->play[pl].state = 1;
        doom->play[pl].vec_grav = 0;
    }
    if (pl == doom->n_play)
		printf("h = %f\n", doom->play[pl].t.y);
    if (doom->play[pl].state)
    {
        doom->play[pl].t.y += doom->play[pl].vec_grav;
		doom->play[pl].vec_grav -= doom->gravity;
//		if (h - doom->play[pl].t.y > 9)
//		}
        if (doom->play[pl].t.y <= h)
        {
        	if (doom->play[pl].vec_grav <= -1.2)
				doom->play[pl].heart = 0;
            doom->play[pl].state = 0;
            doom->play[pl].t.y = h;
        }
    }
}

int     you_win(t_doom *doom)
{
    int pl;
    int res;

    pl = 0;
    res = 0;
    while (pl < doom->max_p)
    {
        if (doom->play[pl].heart && pl != doom->n_play)
            res = 1;
        pl++;
    }
    return (res);
}

void	game(t_doom *doom)
{
	int nb;
	float size;

	nb = 0;
	while (nb < doom->max_p)
	{
		if (nb != doom->n_play)
		{

			size = move_up(doom, nb);
			if (size > 0 && size <= 2)
				doom->play[nb].angle_y += 1;
			else if(size == 0)
				jump_pl(doom, nb, 1);
			jump_pl(doom, nb, 0);
		}
		nb++;
	}
}

void	new_pull(t_doom *doom, int pl, int nb)
{
	doom->pull[nb].t.x = doom->play[pl].t.x;
	doom->pull[nb].t.y = doom->play[pl].t.y + 6;
	doom->pull[nb].t.z = doom->play[pl].t.z;
	doom->pull[nb].vec = rot_vec((t_vec){0, -((float)(doom->play[pl].angle_x * 2) / (float)doom->skybox.indent) - 0.2, 1, 0}, 360 - doom->play[pl].angle_y);
	doom->pull[nb].t.x += doom->pull[nb].vec.x * 2;
	doom->pull[nb].t.y += doom->pull[nb].vec.y * 2;
	doom->pull[nb].t.z += doom->pull[nb].vec.z * 2;
	doom->pull[nb].status = 1;
}

void	vec_pull(t_doom *doom)
{
	int nb;
	t_coliz pull;

	nb = 0;
	if (doom->play[doom->n_play].weapons == 8 && doom->play[doom->n_play].aim.pull == 1)
	{
		while (nb < MAX_PULL && doom->pull[nb].status)
			nb++;
		if (nb < MAX_PULL)
			new_pull(doom, doom->n_play, nb);
	}
	nb = 0;
	while (nb < MAX_PULL)
	{
		if (doom->pull[nb].status > 8)
			doom->pull[nb].status = 0;
		if (doom->pull[nb].status == 1)
		{
			doom->pull[nb].t.x += doom->pull[nb].vec.x * 2;
			doom->pull[nb].t.y += doom->pull[nb].vec.y * 2;
			doom->pull[nb].t.z += doom->pull[nb].vec.z * 2;
			rotate_y(doom, &doom->pull[nb].t);
			core_deg(doom, &doom->pull[nb].t);
			if (doom->pull[nb].t.tz2 > 0.2)
			{
				doom->sp[17].zoom = (1 / doom->pull[nb].t.tz2) * 3;
				print_sp(doom, doom->pull[nb].t.tx1, doom->pull[nb].t.ty1, 17, ((int) (doom->pull[nb].t.tz2 * 100.0) << FIXP16_SHIFT), 0);
			}
		}
		if (doom->pull[nb].status > 1 && doom->nb % 2 == 0)
		{
			rotate_y(doom, &doom->pull[nb].t);
			core_deg(doom, &doom->pull[nb].t);
			if (doom->pull[nb].t.tz2 > 0.2)
			{
				doom->sp[18].zoom = (1 / doom->pull[nb].t.tz2) * 3;
				doom->sp[18].count = doom->pull[nb].status - 1;
				print_sp(doom, doom->pull[nb].t.tx1, doom->pull[nb].t.ty1, 18, ((int) (doom->pull[nb].t.tz2 * 100.0) << FIXP16_SHIFT), 0);
			}
			doom->pull[nb].status++;
		}
		if (doom->pull[nb].status == 1)
		{
			pull = coliz_pull(doom, doom->pull[nb].t.x, doom->pull[nb].t.z, doom->pull[nb].t.y);
			if ((pull.range_min < 1 || doom->pull[nb].t.tz2 > 200))
			{
				doom->sp[18].count = 0;
				if (pull.pl >= 0)
					calc_uron_pl(doom, pull.pl, (int)(5 - (((doom->pull[nb].t.y - doom->play[pull.pl].t.y) * 4) / ((doom->play[pull.pl].crouch) ? 5 : 9))), doom->play[doom->n_play].weapons);
				if (doom->pull[nb].t.tz2 > 0.2)
				{
					doom->sp[18].zoom = (1 / doom->pull[nb].t.tz2) * 2;
					print_sp(doom, doom->pull[nb].t.tx1, doom->pull[nb].t.ty1, 18, ((int) (doom->pull[nb].t.tz2 * 100.0) << FIXP16_SHIFT), 0);
				}
				doom->pull[nb].status++;
			}
		}

		nb++;
	}
}

void	swap_rend(t_doom *doom, int nb)
{
	t_render buff;

	buff = doom->rend[nb];
	doom->rend[nb] = doom->rend[nb + 1];
	doom->rend[nb + 1] = buff;
}

void	sorting_sec(t_doom *doom)
{
	int nb;
	int c;

	c = 1;
	while (c)
	{
		c = 0;
		nb = 0;
		while (nb < doom->max_s - 1)
		{
			if (doom->rend[nb].z > doom->rend[nb + 1].z)
			{
				swap_rend(doom, nb);
				c = 1;
			}
			nb++;
		}
	}
}

void	print_rend(t_doom *doom)
{
	int nb;

	nb = 0;
	while (nb < doom->max_s)
	{
		printf("sort sec = %i len = %f\n", doom->rend[nb].sec, doom->rend[nb].z);
		nb++;
	}
}

void	check_render(t_doom *doom)
{
	t_coliz col;

	col.i = 0;
	col.y = doom->play[doom->n_play].t.y;
	col.pl = -2;
	while (col.i < doom->max_s)
	{
		col.range_min = 100000;
		doom->rend[col.i].sec = col.i;
		min_line_sec(doom, doom->play[doom->n_play].t.x, doom->play[doom->n_play].t.z, &col);
		doom->rend[col.i].z = (doom->sec[col.i].tape == 1) ? col.range_min : 0;
		//printf("sec = %i len = %f\n", col.i, doom->rend[col.i].z);
		col.i++;
	}
	sorting_sec(doom);
//	print_rend(doom);
}

