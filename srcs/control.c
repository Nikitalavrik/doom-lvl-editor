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

int		keyboard_events_down(t_editor *editor, SDL_Event event)
{
	(void)editor;
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (event.key.keysym.sym == SDLK_s)
		editor->flags.t_f.select = editor->flags.t_f.select ? 0 : 1;
	return (0);
}

t_coords	get_coords(t_editor *editor, t_coords mouse)
{
	t_coords	coord;
	double		sq_zoom;

	sq_zoom = SQUARE_SIZE * editor->zoom;
	coord.x = ((mouse.x + editor->center.x + (int)(1 * editor->zoom)) +\
	(mouse.x + editor->center.x + (int)(1 * editor->zoom))) / 2 / sq_zoom;
	coord.y = ((mouse.y + editor->center.y + (int)(1 * editor->zoom)) +\
	(mouse.y + editor->center.y + (int)(1 * editor->zoom))) / 2 / sq_zoom;

	if (coord.x > 0 && coord.x < editor->size.x &&\
		coord.y > 0 && coord.y < editor->size.y)
		return (coord);
	else
	{
		coord.x = INT16_MAX;
		return (coord);
	}
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

void	mouse_motion(t_editor *editor)
{
	t_coords 	mouse_position;
	t_coords	coord;
	t_coords	*finded;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	coord = get_coords(editor, mouse_position);
	if (editor->finded)
		editor->finded->inc = 0;
	if (coord.x != INT16_MAX)
	{
		finded = &editor->coords[coord.y][coord.x];
		if (mouse_position.x <= finded->x + (int)(finded->r * editor->zoom) &&\
			mouse_position.x >= finded->x - (int)(finded->r * editor->zoom) &&\
			mouse_position.y <= finded->y + (int)(finded->r * editor->zoom) &&\
			mouse_position.y >= finded->y - (int)(finded->r * editor->zoom))
			{
				finded->inc = 1;
				finded->r = 2;
				editor->finded = finded;
			}
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
		editor->move_save.y = mouse_position.y;;
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
			editor->flags.t_f.move = editor->flags.t_f.select;
			editor->move_save.x = mouse_position.x;
			editor->move_save.y = mouse_position.y;
	//		if (!editor->flags.t_f.select)
	//			draw_room();
		}
		if (event.type == SDL_MOUSEBUTTONUP && editor->flags.t_f.move)
			editor->flags.t_f.move = 0;
		if (editor->flags.t_f.move)
			mouse_move_map(editor);
		if (event.type == SDL_MOUSEMOTION)
			mouse_motion(editor);
		if (event.type == SDL_KEYDOWN)
		{
			if (keyboard_events_down(editor, event))
				return (1);
		}
	}
	return (0);
}
