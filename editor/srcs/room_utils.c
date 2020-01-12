/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:54:16 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/12 14:29:37 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void    calc_max_min(t_room *room)
{
	t_epoint	*iter;

	iter = room->point;
	room->max_xy.x = iter->x;
	room->max_xy.y = iter->y;
	room->min_xy.x = iter->x;
	room->min_xy.y = iter->y;
	while (iter)
	{
		room->max_xy.x = iter->x > room->max_xy.x ?\
		iter->x : room->max_xy.x;
		room->max_xy.y = iter->y > room->max_xy.y ?\
		iter->y : room->max_xy.y;
		room->min_xy.x = iter->x < room->min_xy.x ?\
		iter->x : room->min_xy.x;
		room->min_xy.y = iter->y < room->min_xy.y ?\
		iter->y : room->min_xy.y;
		iter = iter->next;
	}
	room->area = pow(room->max_xy.x - room->min_xy.x, 2) +\
	pow(room->max_xy.y - room->min_xy.y, 2);
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
	if (editor->point)
	{
		push_room(&editor->rooms, editor->point);
		editor->num_of_rooms++;
		editor->rooms->id = editor->num_of_rooms;
		calc_max_min(editor->rooms);
		editor->point = NULL;
		editor->rooms->alpha = 80;
		editor->rooms->num_of_textures = 2;
		editor->rooms->f_x_angle = 2;
		editor->rooms->f_y_angle = 2;
		editor->rooms->f_height = 2;
		editor->max_sectors++;
		delete_stick_line_room(editor);
		editor->point_cnt = 0;
		sort_rooms(&editor->rooms, editor->num_of_rooms);
	}
}
