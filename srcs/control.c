/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/22 16:26:14 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		detect_event(t_editor *editor)
{
	t_coords 	mouse_position;
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_MOUSEWHEEL)
			mouse_event(editor, event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
			editor->flags.t_f.move = editor->flags.t_f.select;
			editor->move_save.x = mouse_position.x;
			editor->move_save.y = mouse_position.y;
			check_rooms(editor, mouse_position, 1);
			// ft_printf("sprite = %i\n", editor->flags.t_f.sprite);
			if (editor->flags.t_f.sprite && editor->selected)
				add_sprite(editor);
			if (!editor->flags.t_f.select && !editor->flags.t_f.sprite)
				add_line(editor);
		}
		if (event.type == SDL_MOUSEBUTTONUP && editor->flags.t_f.move)
			editor->flags.t_f.move = 0;
		if (editor->flags.t_f.move)
			mouse_move(editor);
		if (event.type == SDL_MOUSEMOTION)
			mouse_motion(editor);
		if (event.type == SDL_KEYDOWN)
			if (keyboard_events_down(editor, event))
				return (1);
		if (event.type == SDL_KEYUP)
			if (keyboard_events_up(editor, event))
				return (1);
	}
	return (0);
}
