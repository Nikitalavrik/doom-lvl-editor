/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:53:48 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 18:16:01 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	mouse_zoom(t_editor *editor, SDL_Event	event)
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

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	check_point(editor, mouse_position);
	if (editor->point_cnt == 1)
		editor->flags.t_f.floor ? stick_room(editor) : stick_line(editor);
	else if (editor->flags.t_f.select)
	{
		if (editor->rooms)
			check_rooms(editor, mouse_position, 0);
		if (editor->lines || editor->selected)
			check_line(editor, mouse_position);
		if (editor->selected)
			check_sprite(editor->selected, mouse_position, editor->zoom);
	}
}

void	mouse_button_down(t_editor *editor)
{
	t_coords 	mouse_position;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	editor->flags.t_f.move = editor->flags.t_f.select;
	editor->move_save.x = mouse_position.x;
	editor->move_save.y = mouse_position.y;
	check_rooms(editor, mouse_position, 1);
	if (!editor->flags.t_f.select)
	{
		if (editor->flags.t_f.sprite && editor->selected)
			add_sprite(editor);
		else if (editor->flags.t_f.line)
			add_line(editor);
		else if (editor->flags.t_f.floor)
			add_room(editor);
	}
}