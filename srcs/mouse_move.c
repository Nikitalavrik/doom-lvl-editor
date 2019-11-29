/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:43:51 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 18:20:30 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

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
	if (!(check_sprite(editor->selected, mouse_position, editor->zoom)))
		mouse_move_map(editor, mouse_position);
	else
		mouse_move_sprite(editor, mouse_position);
}
