/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:55:10 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:51:20 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"


double		calc_short_dist(t_eline *line, t_coords mouse)
{
	double a;
	double b;
	double c;
	double s;
	double h;

	a = pow(mouse.x - line->points[0]->coord->x, 2) + pow(mouse.y - line->points[0]->coord->y, 2);
	b = pow(mouse.x - line->points[1]->coord->x, 2) + pow(mouse.y - line->points[1]->coord->y, 2);
	c = pow(line->points[1]->coord->x - line->points[0]->coord->x, 2) + pow(line->points[1]->coord->y\
	- line->points[0]->coord->y, 2);
	s = abs((mouse.x  - line->points[1]->coord->x) * (line->points[0]->coord->y - line->points[1]->coord->y) -\
	(line->points[0]->coord->x  - line->points[1]->coord->x) * (mouse.y - line->points[1]->coord->y));
	h = 2 * s / sqrt(c);
	if ((a + c) < b || (b + c) < a)
	{
		if (a < b)
			return (sqrt(a));
		if (b < a)
			return (sqrt(b));
	}
	return (h);
}

t_eline	 *check_line(t_editor *editor, t_coords mouse)
{
	double		calc_dist;
	double		min_dist;
	t_eline		*choosen;
	t_eline		*lines;

	lines = editor->lines;
	min_dist = 20;
	choosen = NULL;
	while (lines)
	{
		lines->color = WALL_COLOR;
		calc_dist = calc_short_dist(lines, mouse);	
		if (calc_dist < min_dist)
		{
			min_dist = calc_dist;
			choosen = lines;
		}
		lines = lines->next;
	}
	if (choosen)
		choosen->color = PRESS_WALL_COLOR;
	return (choosen);
}

t_esprite	*check_sprite(t_room *selected, t_coords mouse, double zoom)
{
	int			min;
	t_esprite	*choosen;
	t_esprite	*iter;
	int			dist;

	if (!selected)
		return (NULL);
	iter = selected->sprites;
	min = SPRITE_SIZE * zoom;
	choosen = NULL;
	while (iter)
	{
		iter->flag_a = 0;
		dist = sqrt(pow(mouse.x - iter->coord->x - iter->dist.x, 2) +\
		pow(mouse.y - iter->coord->y - iter->dist.y, 2));
		if (dist < min)
		{
			choosen = iter;
			min = dist;
		}
		iter = iter->next;
	}
	if (choosen)
		choosen->flag_a = 1;
	return (choosen);
}

t_room	*check_rooms(t_editor *editor, t_coords mouse, int type)
{
	t_coords	min;
	t_coords	max;
	t_room		*iter;
	int			min_area;

	iter = editor->rooms;
	min_area = INT16_MAX;
	while (iter && iter->next)
		iter = iter->next;
	while (iter)
	{
		min = editor->coords[iter->min_xy.y][iter->min_xy.x];
		max = editor->coords[iter->max_xy.y][iter->max_xy.x];
		iter->flags.t_f.hover = 0;
		if (mouse.x >= min.x && mouse.x <= max.x\
		&& mouse.y >= min.y && mouse.y <= max.y &&\
		iter->area < min_area)
		{
			iter->flags.t_f.hover = 1;
			min_area = iter->area;
			if (type)
			{
				iter->flags.t_f.select = 1;
				editor->selected = iter;
			}
		}
		else if (type && editor->selected && iter->flags.t_f.select)
		{
			iter->flags.t_f.select = 0;
			editor->flags.t_f.sprite = 0;
			editor->selected = editor->selected == iter ? NULL : editor->selected;
		}
		iter = iter->prev;
	}
	iter = editor->selected;
	return (editor->selected);
}

t_coords	*check_point(t_editor *editor, t_coords mouse_position)
{
	t_coords	coord;
	t_coords	*finded;
	int			tmp;

	coord = get_coords(editor, mouse_position);
	if (editor->finded)
		editor->finded->inc = 0;
	if (coord.x != INT16_MAX)
	{
		finded = &editor->coords[coord.y][coord.x];
		tmp = (int)(finded->r * editor->zoom);
		if (mouse_position.x <= finded->x + tmp &&\
			mouse_position.x >= finded->x - tmp &&\
			mouse_position.y <= finded->y + tmp &&\
			mouse_position.y >= finded->y - tmp)
			{
				finded->inc = 1;
				finded->r = 3;
				editor->finded = finded;
				return (finded);
			}
	}
	return (NULL);
}
