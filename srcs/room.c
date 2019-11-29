/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:55:01 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 15:55:59 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void        push_room(t_room **begin, t_epoint *point)
{
	t_room *iterator;
	t_room *new_point;

	new_point = ft_memalloc(sizeof(t_room));
	new_point->point = point;
	if (*begin)
	{
		iterator = *begin;
		new_point->next = iterator;
		iterator->prev = new_point;
		*begin = new_point;
	}
	else
		*begin = new_point;
}

void		pop_room(t_room **begin)
{
	t_room *next_begin;
	t_room *iterator;

	iterator = *begin;
	if (iterator && iterator->next)
	{
		next_begin = iterator->next;
		next_begin->prev = NULL;
		ft_memdel((void **)&iterator);
		*begin = next_begin;
	}
	else if (iterator)
	{
		ft_memdel((void **)&iterator);
		*begin = NULL;
	}
}


void	add_room(t_editor *editor)
{
	t_coords 	mouse_position;
	t_coords	coord;
	t_coords	*finded;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	coord = get_coords(editor, mouse_position);
	if (coord.x != INT16_MAX)
	{
		finded = &editor->coords[coord.y][coord.x];
		if (mouse_position.x <= finded->x + (int)(finded->r * editor->zoom) &&\
			mouse_position.x >= finded->x - (int)(finded->r * editor->zoom) &&\
			mouse_position.y <= finded->y + (int)(finded->r * editor->zoom) &&\
			mouse_position.y >= finded->y - (int)(finded->r * editor->zoom))
			{
				push_point(&editor->room_point, finded);
				editor->room_point->x = coord.x;
				editor->room_point->y = coord.y;
				editor->point_cnt++;
				if (editor->room_point && editor->room_point->next)
				{
					editor->point_cnt = 0;
					delete_stick_line_room(editor);
					push_room(&editor->rooms, editor->room_point);
					calc_max_min(editor->rooms);
					editor->rooms->alpha = 80;
					editor->max_sectors++;
					editor->num_of_rooms++;
					sort_rooms(&editor->rooms, editor->num_of_rooms);
					editor->room_point = NULL;
				}
			}
	}
}
