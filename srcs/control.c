/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:00:32 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	mouse_events(t_editor *editor, SDL_Event event)
{
	t_coords 	mouse_position;

	if (event.type == SDL_MOUSEWHEEL)
		mouse_zoom(editor, event);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		mouse_button_down(editor);
	if (event.button.clicks == 1 && event.button.button == SDL_BUTTON_RIGHT)
	{
		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		if (check_line(editor, mouse_position))
			choice_win(editor, event, 1);
	}
	if (event.type == SDL_MOUSEBUTTONUP && editor->flags.t_f.move)
		editor->flags.t_f.move = 0;
	if (editor->flags.t_f.move)
		mouse_move(editor);
	if (event.type == SDL_MOUSEMOTION)
		mouse_motion(editor);
}

int		detect_event(t_editor *editor)
{	
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (!editor->flags.t_f.visual)
			mouse_events(editor, event);
		else
			god_rot_move(editor, event);
		if (event.type == SDL_KEYDOWN)
			if (keyboard_events_down(editor, event))
				return (1);
		if (event.type == SDL_KEYUP)
			if (keyboard_events_up(editor, event))
				return (1);
	}
	return (0);
}
