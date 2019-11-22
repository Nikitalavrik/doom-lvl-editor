/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:53:48 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/22 16:34:36 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

t_coords	get_coords(t_editor *editor, t_coords mouse)
{
	t_coords	coord;
	double		sq_zoom;

	sq_zoom = SQUARE_SIZE * editor->zoom;
	coord.x = ((mouse.x + editor->center.x + (int)(2 * editor->zoom)) +\
	(mouse.x + editor->center.x + (int)(2 * editor->zoom))) / 2 / sq_zoom;
	coord.y = ((mouse.y + editor->center.y + (int)(2 * editor->zoom)) +\
	(mouse.y + editor->center.y + (int)(2 * editor->zoom))) / 2 / sq_zoom;

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
				finded->r = 3;
				editor->finded = finded;
			}
	}
	if (editor->rooms)
		check_rooms(editor, mouse_position, 0);
	if (editor->lines || editor->selected)
		check_line(editor, mouse_position);
	if (editor->selected)
		check_sprite(editor->selected, mouse_position, editor->zoom);
}

void	mouse_move_map(t_editor *editor, t_coords mouse_position)
{
	t_coords	tmp_calc;
	t_coords	limit;

	if ((mouse_position.x != editor->move_save.x ||\
		mouse_position.y != editor->move_save.y))
	{
		limit.x = SQUARE_SIZE * editor->size.x * editor->zoom -\
		editor->width + MENU_WIDTH + PADDING_WIDTH;
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
	}
}

void	mouse_move_sprite(t_editor *editor, t_coords mouse_position)
{
	t_dcoords	tmp_calc;
	t_esprite	*sprite;

	if (editor->selected)
		sprite = check_sprite(editor->selected, mouse_position, editor->zoom);
	if ((mouse_position.x != editor->move_save.x ||\
		mouse_position.y != editor->move_save.y) && sprite)
	{
		tmp_calc.x = (double)((mouse_position.x - editor->move_save.x) / editor->zoom) + sprite->move.x;
		tmp_calc.y = (double)((mouse_position.y - editor->move_save.y) / editor->zoom) + sprite->move.y;
		// if (tmp_calc.x )
		sprite->move.x = tmp_calc.x;
		sprite->move.y = tmp_calc.y;
		editor->move_save.x = mouse_position.x;
		editor->move_save.y = mouse_position.y;
	}
}

void	mouse_move(t_editor *editor)
{
	t_coords 	mouse_position;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if (!editor->flags.t_f.sprite)
		mouse_move_map(editor, mouse_position);
	else
		mouse_move_sprite(editor, mouse_position);
}

