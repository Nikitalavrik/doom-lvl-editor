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
	t_coords	tmp_calc;
	t_coords	limit;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if ((mouse_position.x != editor->move_save.x ||\
		mouse_position.y != editor->move_save.y))
	{
		limit.x = SQUARE_SIZE * editor->size.x * editor->zoom - editor->width + MENU_WIDTH + PADDING_WIDTH;
		limit.y = SQUARE_SIZE * editor->size.y * editor->zoom - editor->height;
		tmp_calc.x = mouse_position.x - editor->move_save.x;
		tmp_calc.y = mouse_position.y - editor->move_save.y;
		if ((editor->center.x > 0 ||  tmp_calc.x < 0) &&\
		(editor->center.x < limit.x || tmp_calc.x > 0))
			editor->center.x -= tmp_calc.x;
		if ((editor->center.y > 0 || tmp_calc.y < 0) &&\
		(editor->center.y < limit.y || tmp_calc.y > 0))
			editor->center.y -= tmp_calc.y;
		editor->move_save.x = mouse_position.x;
		editor->move_save.y = mouse_position.y;
		// ft_printf("limit  x %i y %i\n", limit.x, limit.y);
		// ft_printf("center x %i y %i\n", editor->center.x, editor->center.y);
	}
}

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
			editor->move = 1;
			editor->move_save.x = mouse_position.x;
			editor->move_save.y = mouse_position.y;
		}

		if (event.type == SDL_MOUSEBUTTONUP)
			editor->move = 0;
		if (editor->move)
			mouse_move_map(editor);
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (keyboard_events(editor, event))
				return (1);
		}
	}
	return (0);
}
