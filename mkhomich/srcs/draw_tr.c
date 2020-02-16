/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhomich <mkhomich@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:27:31 by mkhomich          #+#    #+#             */
/*   Updated: 2019/09/23 11:27:33 by mkhomich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	swap_toch(t_point *t1, t_point *t2)
{
	t_point temp;

	temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}

int		clip_y(t_inter *l, t_inter *r, t_drtr *i, int y)
{
	while (y < 0)
	{
		dx(l, r, i);
		iter(l);
		iter(r);
		y++;
	}
	return (y);
}

void	draw_top_tri(t_triangl *tr, t_doom *doom, int *text, int tape)
{
	t_drtr	i;
	t_inter	l;
	t_inter	r;

	if (tr->t2.x < tr->t1.x)
		swap_toch(&tr->t1, &tr->t2);
	l = interpol(tr->t1, tr->t3, tape);
	r = interpol(tr->t2, tr->t3, tape);
	i.temp_y = tr->t1.y;
	while (i.temp_y <= tr->t3.y && i.temp_y < doom->h)
	{
		dx(&l, &r, &i);
		draw_line(doom, &i, text, tape);
		iter(&l);
		iter(&r);
		i.temp_y++;
	}
}

void	draw_bottom_tri(t_triangl *tr, t_doom *doom, int *text, int tape)
{
	t_drtr	i;
	t_inter	l;
	t_inter	r;

	if (tr->t3.x < tr->t2.x)
		swap_toch(&tr->t2, &tr->t3);
	l = interpol(tr->t1, tr->t2, tape);
	r = interpol(tr->t1, tr->t3, tape);
	i.temp_y = tr->t1.y;
	while (i.temp_y <= tr->t3.y && i.temp_y < doom->h)
	{
		dx(&l, &r, &i);
		draw_line(doom, &i, text, tape);
		iter(&l);
		iter(&r);
		i.temp_y++;
	}
}

void	draw_triangl_all(t_triangl *tr, t_doom *doom, int *text, int tape)
{
	t_drtr	i;
	t_inter	l;
	t_inter	r;
	int		height;

	height = tr->t3.y;
	i.new_x = tr->t1.x + (0.5 + (tr->t2.y - tr->t1.y) *
			(tr->t3.x - tr->t1.x) / (tr->t3.y - tr->t1.y));
	if (tr->t2.x > i.new_x)
		swap_toch(&tr->t2, &tr->t3);
	l = interpol(tr->t1, tr->t2, tape);
	r = interpol(tr->t1, tr->t3, tape);
	i.temp_y = tr->t1.y;
	while (i.temp_y <= height && i.temp_y < doom->h)
	{
		dx(&l, &r, &i);
		draw_line(doom, &i, text, tape);
		if (i.temp_y == tr->t2.y)
			l = interpol(tr->t2, tr->t3, tape);
		else if (i.temp_y == tr->t3.y)
			r = interpol(tr->t3, tr->t2, tape);
		iter(&l);
		iter(&r);
		i.temp_y++;
	}
}

void	draw_triangl(t_doom *doom, t_triangl *tr, int *text, int tape)
{
	if ((tr->t1.x == tr->t2.x && tr->t2.x == tr->t3.x)
		|| (tr->t1.y == tr->t2.y && tr->t2.y == tr->t3.y))
		return ;
	if (tr->t2.y < tr->t1.y)
		swap_toch(&tr->t1, &tr->t2);
	if (tr->t3.y < tr->t1.y)
		swap_toch(&tr->t1, &tr->t3);
	if (tr->t3.y < tr->t2.y)
		swap_toch(&tr->t3, &tr->t2);
	if (tr->t1.y == tr->t2.y)
		draw_top_tri(tr, doom, text, tape);
	else if (tr->t2.y == tr->t3.y)
		draw_bottom_tri(tr, doom, text, tape);
	else
		draw_triangl_all(tr, doom, text, tape);
}


