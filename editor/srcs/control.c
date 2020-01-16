/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/12 14:02:00 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	right_click_event(t_editor *editor, SDL_Event event)
{
	t_coords 	mouse_position;
	void		*param;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if ((param = check_line(editor, mouse_position)))
		choice_win(editor, event, 1, param);
	else if ((param = check_sprite(editor->rooms, mouse_position, editor->zoom)))
		choice_win(editor, event, 3, param);
	else if ((param = check_rooms(editor, mouse_position, 1)))
		choice_win(editor, event, 2, param);
}

void	mouse_events(t_editor *editor, SDL_Event event)
{
	t_coords 	mouse_position;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if (mouse_position.x < editor->width - MENU_WIDTH)
	{
		if (event.type == SDL_MOUSEWHEEL)
			mouse_zoom(editor, event);
		if (event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
			mouse_button_down(editor);
		if (event.button.clicks == 1 && event.button.button == SDL_BUTTON_RIGHT)
			right_click_event(editor, event);
		if (event.type == SDL_MOUSEBUTTONUP && editor->flags.t_f.move)
			editor->flags.t_f.move = 0;
		if (editor->flags.t_f.move)
			mouse_move(editor);
		if (event.type == SDL_MOUSEMOTION)
			mouse_motion(editor);
	}
	else
		editor_menu_events(editor, mouse_position, event);
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
