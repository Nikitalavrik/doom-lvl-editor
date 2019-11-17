/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:21:12 by nikita            #+#    #+#             */
/*   Updated: 2019/11/17 19:46:12 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

// need add func that find nearest point and auto completion

t_coords     *check_room(t_editor *editor, int *x, int *y)
{
	t_point *begin;
	t_point *end;

	end = NULL;
	begin = editor->point;
	if (begin)
	{
		end = editor->point;
		while (end->next)
			end = end->next;
		if (end->coord == begin->coord)
			return (NULL);
	}
	else
		return (NULL);
	*x = end->x;
	*y = end->y;
	return (end->coord);
}

void    calc_max_min(t_editor *editor)
{
	t_point	*iter;

	iter = editor->rooms->point;
	editor->rooms->max_xy.x = iter->x;
	editor->rooms->max_xy.y = iter->y;
	editor->rooms->min_xy.x = iter->x;
	editor->rooms->min_xy.y = iter->y;
	while (iter)
	{
		editor->rooms->max_xy.x = iter->x > editor->rooms->max_xy.x ?\
		iter->x : editor->rooms->max_xy.x;
		editor->rooms->max_xy.y = iter->y > editor->rooms->max_xy.y ?\
		iter->y : editor->rooms->max_xy.y;
		editor->rooms->min_xy.x = iter->x < editor->rooms->min_xy.x ?\
		iter->x : editor->rooms->min_xy.x;
		editor->rooms->min_xy.y = iter->y < editor->rooms->min_xy.y ?\
		iter->y : editor->rooms->min_xy.y;
		iter = iter->next;
	}
	editor->rooms->area = pow(editor->rooms->max_xy.x - editor->rooms->min_xy.x, 2) +\
	pow(editor->rooms->max_xy.y - editor->rooms->min_xy.y, 2);
}

void    close_room(t_editor *editor)
{
	int			x;
	int			y;
	t_coords    *last;

	if ((last = check_room(editor, &x, &y)))
	{
		push_point(&editor->point, last);
		editor->point->x = x;
		editor->point->y = y;
		push_line(&editor->lines, editor->point, editor->point->next);
		editor->lines->color = WALL_COLOR;
		editor->lines->id = editor->line_id;
		editor->line_id++;
	}
	push_room(&editor->rooms, editor->point);
	editor->num_of_rooms++;
	editor->rooms->id = editor->num_of_rooms;
	calc_max_min(editor);
	editor->point = NULL;
	editor->rooms->lines = editor->lines;
	editor->lines = NULL;
	editor->rooms->alpha = 80;
	// sort_rooms(editor->rooms);
}
