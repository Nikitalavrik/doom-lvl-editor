/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:21:12 by nikita            #+#    #+#             */
/*   Updated: 2019/11/16 17:18:01 by nlavrine         ###   ########.fr       */
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

// can be optimize

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
}

// t_coords	*find_coords()

// void	init_points(t_editor *editor, t_room *room)
// {
// 	t_coords 		iter;
// 	t_coords 		max;

// 	iter.x = iterate_room->min_xy.x;	
// 	max.x = iterate_room->max_xy.x;
// 	max.y = iterate_room->max_xy.y;
// 	while (iter.x < max.x)
// 	{
// 		iter.y = iterate_room->min_xy.y;
// 		while (iter.y < max.y)
// 		{
// 			if ()
// 			iter.y++;
// 		}
// 		iter.x++;
// 	}
// }

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
	}
	push_room(&editor->rooms, editor->point);
	editor->num_of_rooms++;
	editor->rooms->id = editor->num_of_rooms;
	calc_max_min(editor);
	editor->point = NULL;
	// init_points(editor, editor->rooms);
	ft_printf("max x = %i y = %i\nmin x = %i y = %i\n",
	editor->rooms->max_xy.x, editor->rooms->max_xy.y,
	editor->rooms->min_xy.x, editor->rooms->min_xy.y);
}
