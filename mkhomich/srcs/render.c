/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:22:11 by mkhomich          #+#    #+#             */
/*   Updated: 2019/12/28 17:58:03 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

int		check_viem_tr(t_triangl *tr, t_doom *doom)
{
	return ((tr->t1.x >= -1000 && tr->t1.x < doom->surface->w + 1000 &&
	tr->t1.y >= -1000 && tr->t1.y < doom->surface->h + 1000) ||
	(tr->t2.x >= -1000 && tr->t2.x < doom->surface->w + 1000 &&
	tr->t2.y >= -1000 && tr->t2.y < doom->surface->h + 1000) ||
	(tr->t3.x >= -1000 && tr->t3.x < doom->surface->w + 1000 &&
	tr->t3.y >= -1000 && tr->t3.y < doom->surface->h + 1000));
}

void    vector_cal(t_toch start, t_toch end, t_vec *res)
{
	res->x = start.tx2 - end.tx2;
	res->y = start.ty2 - end.ty2;
	res->z = start.tz2 - end.tz2;
}

float		tr_point(t_doom *doom, t_toch st, t_toch end, t_point *p)
{
	t_vec v;
	float cof;
	t_toch new;

	if (st.tz2 > doom->min_z)
	{
		p->x = st.tx1;
		p->y = st.ty1;
		p->z = (1 << FIXP28_SHIFT) / st.tz2;
	}
	else
	{
		vector_cal(st, end, &v);
		cof = (end.tz2 - doom->min_z) / (end.tz2 - st.tz2);
		new.tx2 = end.tx2 + (v.x * cof);
		new.ty2 = end.ty2 + (v.y * cof);
		new.tz2 = end.tz2 + (v.z * cof);
		core_deg(doom, &new);
		p->x = new.tx1;
		p->y = new.ty1;
		p->z = (1 << FIXP28_SHIFT) / doom->min_z;
		return (cof);
	}
	return (1);
}

int cal_point_zmin(t_toch t1, t_toch t2, t_toch t3, t_doom *doom)
{
	return ((t1.tz2 <= doom->min_z) + (t2.tz2 <= doom->min_z) + (t3.tz2 <= doom->min_z));
}

void	cut_triang1(t_doom *doom, t_sec *sec, int x, int y, int text)
{
	t_triangl	tr1;
	t_triangl	tr2;
	int 		tape;
	float		cof;

	tape = cal_point_zmin(sec->toch[y][x], sec->toch[y][x + 1], sec->toch[y + 1][x + 1], doom);
	if (tape == 1)
	{
		cof = tr_point(doom, sec->toch[y][x], sec->toch[y][x + 1], &tr1.t1);
		if (cof == 1.0)
		{
			tr1.t1.u = 0;
			tr1.t1.v = 0;
		}
		else if (cof >= 0 && cof <= 1)
		{
			tr1.t1.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tr1.t1.v = 0;
			tr2.t1 = tr1.t1;

			cof = tr_point(doom, sec->toch[y][x], sec->toch[y + 1][x + 1], &tr2.t3);
			tr2.t3.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tr2.t3.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tape = 2;
		}
		cof = tr_point(doom, sec->toch[y][x + 1], sec->toch[y + 1][x + 1], &tr1.t2);
		if (cof == 1.0)
		{
			tr1.t2.u = ((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / sec->toch[y][x + 1].tz2;
			tr1.t2.v = 0;
		}
		else if (cof >= 0 && cof <= 1)
		{
			tr1.t2.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z);
			tr1.t2.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tr2.t1 = tr1.t2;
			tr2.t2 = tr1.t1;
			cof = tr_point(doom, sec->toch[y][x + 1], sec->toch[y][x], &tr2.t3);
			tr2.t3.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);
			tr2.t3.v = 0;
		}
		cof = tr_point(doom, sec->toch[y + 1][x + 1], sec->toch[y][x], &tr1.t3);
		if (cof == 1.0)
		{
			tr1.t3.u = ((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / sec->toch[y + 1][x + 1].tz2;
			tr1.t3.v = ((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / sec->toch[y + 1][x + 1].tz2;
			if (tape == 2)
				tr2.t2 = tr1.t3;
		}
		else if (cof >= 0 && cof <= 1)
		{
			tr1.t3.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);
			tr1.t3.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);

			tr2.t1 = tr1.t3;
			tr2.t2 = tr1.t2;
			cof = tr_point(doom, sec->toch[y + 1][x + 1], sec->toch[y][x + 1], &tr2.t3);
			tr2.t3.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z);
			tr2.t3.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
		}
		if (check_viem_tr(&tr1, doom))
			draw_triangl(doom, &tr1, text, 0);
		if (check_viem_tr(&tr2, doom) && tape == 1)
			draw_triangl(doom, &tr2, text, 0);
	}
}

void	cut_triang2(t_doom *doom, t_sec *sec, int x, int y, int text)
{
	t_triangl	tr1;
	t_triangl	tr2;
	int 		tape;
	float		cof;

	tape = cal_point_zmin(sec->toch[y + 1][x + 1], sec->toch[y + 1][x], sec->toch[y][x], doom);
	if (tape == 1)
	{
		cof = tr_point(doom, sec->toch[y + 1][x + 1], sec->toch[y + 1][x], &tr1.t1);
		if (cof == 1.0)
		{
			tr1.t1.u = ((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / sec->toch[y + 1][x + 1].tz2;
			tr1.t1.v = ((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / sec->toch[y + 1][x + 1].tz2;
		}
		else if (cof >= 0 && cof <= 1)
		{
			tr1.t1.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);
			tr1.t1.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z);
			tr2.t2 = tr1.t1;
			cof = tr_point(doom, sec->toch[y + 1][x + 1], sec->toch[y][x], &tr2.t1);
			tr2.t1.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);
			tr2.t1.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);
			tape = 4;
		}
		cof = tr_point(doom, sec->toch[y + 1][x], sec->toch[y][x], &tr1.t2);
		if (cof == 1.0)
		{
			tr1.t2.u = 0;
			tr1.t2.v = ((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / sec->toch[y + 1][x].tz2;
		}
		else if (cof >= 0 && cof <= 1)
		{
			tr1.t2.u = 0;
			tr1.t2.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (cof);
			tr2.t3 = tr1.t1;
			tr2.t2 = tr1.t2;
			cof = tr_point(doom, sec->toch[y + 1][x], sec->toch[y + 1][x + 1], &tr2.t1);
			tr2.t1.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tr2.t1.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z);
		}
		cof = tr_point(doom, sec->toch[y][x], sec->toch[y + 1][x + 1], &tr1.t3);
		if (cof == 1.0)
		{
			tr1.t3.u = 0;
			tr1.t3.v = 0;
			if (tape == 4)
				tr2.t3 = tr1.t3;
		}
		else if (cof >= 0 && cof <= 1)
		{
			tr1.t3.u = (((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tr1.t3.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
			tr2.t1 = tr1.t3;
			tr2.t2 = tr1.t2;
			cof = tr_point(doom, sec->toch[y][x], sec->toch[y + 1][x], &tr2.t3);
			tr2.t3.u = 0;
			tr2.t3.v = (((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << FIXP22_SHIFT) / doom->min_z) * (1 - cof);
		}
		if (check_viem_tr(&tr1, doom))
			draw_triangl(doom, &tr1, text, 0);
		if (check_viem_tr(&tr2, doom))
			draw_triangl(doom, &tr2, text, 0);
	}
}

void	render_tr1(t_doom *doom, t_sec *sec, int x, int y)
{
	t_triangl	tr1;
	int			text;
	int			tape;

	if (!(x >= sec->win.x && x < sec->win.x + sec->win.w &&
	y >= sec->win.y && y < sec->win.y + sec->win.h))
		text = sec->t_full;
	else
		text = sec->t_win;
	if (sec->toch[y][x].tz2 > 50)
		tape = 1;
	else
		tape = 0;
	if (sec->toch[y][x].tz2 > doom->min_z && sec->toch[y][x + 1].tz2 > doom->min_z && sec->toch[y + 1][x + 1].tz2 > doom->min_z && text)
	{
		tr1.t1.x = sec->toch[y][x].tx1;
		tr1.t1.y = sec->toch[y][x].ty1;
		tr1.t1.u = 0;
		tr1.t1.v = 0;
		tr1.t1.z = (1 << FIXP28_SHIFT) / sec->toch[y][x].tz2;
		tr1.t2.x = sec->toch[y][x + 1].tx1;
		tr1.t2.y = sec->toch[y][x + 1].ty1;
		tr1.t2.u = ((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << ((tape) ? 0 : FIXP22_SHIFT)) / ((tape) ? 1 : sec->toch[y][x + 1].tz2);
		tr1.t2.z = (1 << FIXP28_SHIFT) / sec->toch[y][x + 1].tz2;
		tr1.t2.v = 0;
		tr1.t3.x = sec->toch[y + 1][x + 1].tx1;
		tr1.t3.y = sec->toch[y + 1][x + 1].ty1;
		tr1.t3.u = ((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << ((tape) ? 0 : FIXP22_SHIFT)) / ((tape) ? 1 : sec->toch[y + 1][x + 1].tz2);
		tr1.t3.v = ((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << ((tape) ? 0 : FIXP22_SHIFT)) / ((tape) ? 1 : sec->toch[y + 1][x + 1].tz2);
		tr1.t3.z = (1 << FIXP28_SHIFT) / sec->toch[y + 1][x + 1].tz2;
		if (check_viem_tr(&tr1, doom))
			draw_triangl(doom, &tr1, text, tape);
	}
	else if ((sec->toch[y][x].tz2 > doom->min_z || sec->toch[y][x + 1].tz2 > doom->min_z || sec->toch[y + 1][x + 1].tz2 > doom->min_z) && text)
		cut_triang1(doom, sec, x, y, text);
}

void	render_tr2(t_doom *doom, t_sec *sec, int x, int y)
{
	t_triangl	tr2;
	int			text;
	int			tape;

	if (!(x >= sec->win.x && x < sec->win.x + sec->win.w &&
		y >= sec->win.y && y < sec->win.y + sec->win.h))
		text = sec->t_full;
	else
		text = sec->t_win;
	if (sec->toch[y][x].tz2 > 50)
		tape = 1;
	else
		tape = 0;
	if	(sec->toch[y + 1][x + 1].tz2 > doom->min_z && sec->toch[y + 1][x].tz2 > doom->min_z && sec->toch[y][x].tz2 > doom->min_z && text)
	{
		tr2.t1.x = sec->toch[y + 1][x + 1].tx1;
		tr2.t1.y = sec->toch[y + 1][x + 1].ty1;
		tr2.t1.u = ((((sec->tex_x - x) < 1) ? (int)(doom->text[text].w * (sec->tex_x - x)) : doom->text[text].w - 1) << ((tape) ? 0 : FIXP22_SHIFT)) / ((tape) ? 1 : sec->toch[y + 1][x + 1].tz2);
		tr2.t1.v = ((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << ((tape) ? 0 : FIXP22_SHIFT)) / ((tape) ? 1 : sec->toch[y + 1][x + 1].tz2);
		tr2.t1.z = (1 << FIXP28_SHIFT) / sec->toch[y + 1][x + 1].tz2;
		tr2.t2.x = sec->toch[y + 1][x].tx1;
		tr2.t2.y = sec->toch[y + 1][x].ty1;
		tr2.t2.u = 0;
		tr2.t2.v = ((((sec->tex_y - y) < 1) ? (int)(doom->text[text].h * (sec->tex_y - y)) : doom->text[text].h - 1) << ((tape) ? 0 : FIXP22_SHIFT)) / ((tape) ? 1 : sec->toch[y + 1][x].tz2);
		tr2.t2.z = (1 << FIXP28_SHIFT) / sec->toch[y + 1][x].tz2;
		tr2.t3.x = sec->toch[y][x].tx1;
		tr2.t3.y = sec->toch[y][x].ty1;
		tr2.t3.u = 0;
		tr2.t3.v = 0;
		tr2.t3.z = (1 << FIXP28_SHIFT) / sec->toch[y][x].tz2;
		if (check_viem_tr(&tr2, doom))
			draw_triangl(doom, &tr2, text, tape);
	}
	else if ((sec->toch[y + 1][x + 1].tz2 > doom->min_z || sec->toch[y + 1][x].tz2 > doom->min_z || sec->toch[y][x].tz2 > doom->min_z) && text)
		cut_triang2(doom, sec, x, y, text);
}
