/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/10 16:47:11 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		keyboard_events(t_editor *editor, SDL_Event event)
{
	(void)editor;
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	// if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
	// 	move_up_down(editor, add_double);
	// if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
	// 	move_up_down(editor, sub_double);
	// if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
	// 	rot_by_angl(editor, editor->frame * 3);
	// if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
	// 	rot_by_angl(editor, -editor->frame * 3);
	// if (event.key.keysym.sym == SDLK_h && event.type != SDL_KEYUP)
	// 	editor->txt = editor->txt ? 0 : 1;
	// if (event.key.keysym.sym == SDLK_LSHIFT)
	// 	editor->speed = editor->speed == 0.05 ? 0.1 : 0.05;
	// if (event.key.keysym.sym == SDLK_m && event.type != SDL_KEYUP)
	// {
	// 	editor->mouse = editor->mouse ? 0 : 1;
	// 	editor->mouse ? SDL_SetRelativeMouseMode(SDL_ENABLE) :\
	// 	SDL_SetRelativeMouseMode(SDL_DISABLE);
	// }
	return (0);
}

void	mouse_event(t_editor *editor, SDL_Event	event)
{
	(void)event;
	(void)editor;
}

int		detect_event(t_editor *editor)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_MOUSEMOTION)
			mouse_event(editor, event);
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (keyboard_events(editor, event))
				return (1);
		}
	}
	return (0);
}
