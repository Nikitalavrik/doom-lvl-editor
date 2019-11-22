/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:21:12 by nikita            #+#    #+#             */
/*   Updated: 2019/11/22 13:47:16 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

// need add func that find nearest point and auto completion

t_coords     *check_room(t_editor *editor, int *x, int *y)
{
	t_epoint *begin;
	t_epoint *end;

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
	t_epoint	*iter;

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

void	swap_rooms(t_room **begin, t_room *first, t_room *second)
{
	t_room	*tmp;

	tmp = first->prev;
	if (tmp)
		tmp->next = second;
	tmp = second->next;
	if (tmp)
		tmp->prev = first;
	first->next = second->next;
	second->prev = first->prev;
	first->prev = second;
	second->next = first;
	if (first == *begin)
		*begin = second;
}

void	sort_rooms(t_room **rooms, int len)
{
	int		i;
	t_room	*iter;

	i = 0;
	while (i < len)
	{
		iter = *rooms;
		while (iter && iter->next)
		{
			if (iter->area < iter->next->area)
				swap_rooms(rooms, iter, iter->next);
			iter = iter->next;
		}
		i++;
	}
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
	// ft_printf("**********************\n");
	sort_rooms(&editor->rooms, editor->num_of_rooms);
}
