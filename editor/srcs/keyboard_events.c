/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:16:36 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/30 16:42:06 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	find_and_delete(t_editor *editor)
{
	t_room		*room;
	t_eline		*line;
	t_esprite	*sprite;
	t_coords 	mouse_position;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if ((line = check_line(editor, mouse_position)))
	{
		delete_line(editor, line);
		editor->max_sectors--;
	}
	else if ((sprite = check_sprite(editor->selected,
									mouse_position, editor->zoom)))
		delete_sprite(editor, sprite);
	else if ((room = check_rooms(editor, mouse_position, 1)))
	{
		delete_room(editor, room);
		editor->selected = NULL;
		editor->max_sectors--;
	}
}

void	delete_prev(t_editor *editor)
{
	if (editor->stick_line)
		delete_stick_line_room(editor);
	else
	{
		if (editor->lines)
		{
			pop_line(&editor->lines);
			editor->max_sectors--;
		}	
		if (editor->point)
			pop_point(&editor->point);
	}
	editor->point_cnt = 0;
}

void	clear_level(t_editor *editor)
{
	t_room *room;
	t_room *next_room;
	t_eline *line;
	t_eline *next_line;

	room = editor->rooms;
	while (room)
	{
		next_room = room->next;
		if (room->floor == editor->floor)
			delete_room(editor, room);
		room = next_room;
	}
	line = editor->lines;
	while (line)
	{
		next_line = line->next;
		if (line->floor == editor->floor)
			delete_line(editor, line);
		line = next_line;
	}
}
