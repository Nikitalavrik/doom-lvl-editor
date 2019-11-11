/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/11 18:11:09 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		keyboard_events(t_editor *editor, SDL_Event event)
{
	(void)editor;
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	return (0);
}

t_coords	get_coords(t_editor *editor, t_coords mouse, double sq_zoom)
{
	int	x;
	int	y;

	x = (mouse.x + editor->center.x) / sq_zoom;
	y = (mouse.y + editor->center.y) / sq_zoom;
	if (x > 0 && x < editor->size.x && y > 0 && y < editor->size.y)
		return (editor->coords[y][x]);
	else
		return (mouse);
}

void	mouse_event(t_editor *editor, SDL_Event	event)
{
	t_coords 	mouse_position;
	double		sq_zoom;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	sq_zoom = SQUARE_SIZE * editor->zoom;
	if (event.wheel.y > 0 && editor->zoom < 20)
	{
		editor->center.x = ((mouse_position.x + editor->center.x) / sq_zoom) *\
		(SQUARE_SIZE * (editor->zoom * 1.02)) - mouse_position.x;
		editor->center.y = ((mouse_position.y + editor->center.y) / sq_zoom)*\
		(SQUARE_SIZE * (editor->zoom * 1.02)) - mouse_position.y;
		editor->zoom *= 1.02;
	}
	else if (event.wheel.y < 0 && editor->zoom > 0.16)
	{
		editor->center.x = ((mouse_position.x + editor->center.x) / sq_zoom) *\
		(SQUARE_SIZE * (editor->zoom * 0.95)) - mouse_position.x;
		editor->center.y = ((mouse_position.y + editor->center.y) / sq_zoom)*\
		(SQUARE_SIZE * (editor->zoom * 0.95)) - mouse_position.y;
		editor->zoom *= 0.95;
	}
}

void	mouse_move_map(t_editor *editor)
{
	t_coords 	mouse_position;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	editor->move_map.x = editor->move_save.x + mouse_position.x / 2;
	editor->move_map.y = editor->move_save.y + mouse_position.y / 2;
	// ft_printf("preees\n");
}

int		detect_event(t_editor *editor)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_MOUSEWHEEL)
			mouse_event(editor, event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			editor->move = 1;
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			editor->move_save.x = editor->move_map.x;
			editor->move_save.y = editor->move_map.y;
			editor->move = 0;
		}

		if (editor->move)
			mouse_move_map(editor);
		// if (event.type == SDL_MOUSEMOTION)
		// 	mouse_event(editor, event);
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (keyboard_events(editor, event))
				return (1);
		}
	}
	return (0);
}
