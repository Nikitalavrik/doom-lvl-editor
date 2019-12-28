/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:16:36 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:53:09 by nlavrine         ###   ########.fr       */
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
