/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:55:10 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/20 17:12:45 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

t_eline		*check_line(t_editor *editor, t_coords mouse)
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
		if (editor->floor == lines->floor)
		{
			calc_dist = calc_short_dist(lines, mouse);
			if (calc_dist < min_dist)
			{
				min_dist = calc_dist;
				choosen = lines;
			}
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

void		check_hover_room(t_editor *editor, t_coords mouse, t_room *iter,
													t_coords min_max_area[3])
{
	t_coords	min;
	t_coords	max;

	min = min_max_area[0];
	max = min_max_area[1];
	if (mouse.x >= min.x && mouse.x <= max.x\
	&& mouse.y >= min.y && mouse.y <= max.y && iter->area < min_max_area[2].x)
	{
		iter->flags.t_f.hover = 1;
		(&min_max_area[2])->x = iter->area;
		if (min_max_area[2].y)
		{
			iter->flags.t_f.select = 1;
			editor->selected = iter;
		}
	}
	else if (min_max_area[2].y && editor->selected && iter->flags.t_f.select)
	{
		iter->flags.t_f.select = 0;
		editor->flags.t_f.sprite = 0;
		editor->selected = editor->selected == iter ? NULL : editor->selected;
	}
}

t_room		*check_rooms(t_editor *editor, t_coords mouse, int type)
{
	t_room		*iter;
	t_coords	min_max_area[3];

	iter = editor->rooms;
	min_max_area[2].x = INT16_MAX;
	min_max_area[2].y = type;
	while (iter && iter->next)
		iter = iter->next;
	while (iter)
	{
		min_max_area[0] = editor->coords[iter->min_xy.y][iter->min_xy.x];
		min_max_area[1] = editor->coords[iter->max_xy.y][iter->max_xy.x];
		iter->flags.t_f.hover = 0;
		if (editor->floor == iter->floor)
			check_hover_room(editor, mouse, iter, min_max_area);
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
