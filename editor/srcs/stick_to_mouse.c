/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stick_to_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:06:32 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/26 13:09:39 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	delete_stick_line_room(t_editor *editor)
{
	if (editor->stick_point)
	{
		ft_memdel((void **)&editor->stick_point->coord);
		pop_point(&editor->stick_point);
		editor->stick_point = NULL;
		if (editor->stick_line)
			pop_line(&editor->stick_line);
		if (editor->stick_room)
			pop_room(&editor->stick_room);
	}
}

void	stick_line(t_editor *editor)
{
	t_coords 	*mouse;

	mouse = ft_memalloc(sizeof(t_coords));
	SDL_GetMouseState(&mouse->x, &mouse->y);
	if (editor->point)
	{
		delete_stick_line_room(editor);
		push_point(&editor->stick_point, mouse);
		push_line(&editor->stick_line, editor->point, editor->stick_point);
		editor->stick_line->color = WALL_COLOR;
	}
}

void	stick_room(t_editor *editor)
{
	t_coords 		*mouse;
	t_epoint		*tmp;

	mouse = ft_memalloc(sizeof(t_coords));
	SDL_GetMouseState(&mouse->x, &mouse->y);
	// ft_printf("11\n");
	if (editor->room_point)
	{
		delete_stick_line_room(editor);
		push_point(&editor->stick_point, mouse);
		tmp = editor->stick_point;
		tmp->next = editor->room_point;
		push_room(&editor->stick_room, tmp);
		editor->stick_room->alpha = 100;
	}
}
