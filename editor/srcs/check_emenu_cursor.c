/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_emenu_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:27:35 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/23 15:27:36 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	check_emenu_cursor4(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.clear_lvl))
	{
		editor->param_flag = 10;
	}
	else if (check_position(mouse_position, editor->menu.select_b))
	{
		editor->param_flag = 11;
	}
	else if (!check_emenu_scursor(editor, mouse_position))
		editor->param_flag = 0;
}

void	check_emenu_cursor3(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.return_butt))
	{
		editor->param_flag = 7;
	}
	else if (check_position(mouse_position, editor->menu.save_butt))
	{
		editor->param_flag = 8;
	}
	else if (mouse_position.x >= editor->menu.load_butt.x &&
		mouse_position.x <= editor->menu.load_butt.x1 &&
		mouse_position.y >= editor->menu.load_butt.y &&
		mouse_position.y <= editor->menu.load_butt.y1)
	{
		editor->param_flag = 9;
	}
	else
		check_emenu_cursor4(editor, mouse_position);
}

void	check_emenu_cursor2(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.t_cb_coord))
	{
		editor->param_flag = 4;
	}
	else if (check_position(mouse_position, editor->menu.del_cb_coord))
	{
		editor->param_flag = 5;
	}
	else if (check_position(mouse_position, editor->menu.clo_cb_coord))
	{
		editor->param_flag = 6;
	}
	else
		check_emenu_cursor3(editor, mouse_position);
}

void	check_emenu_cursor(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.coord))
		editor->param_flag = 1;
	else if (check_position(mouse_position, editor->menu.f_cb_coord))
	{
		editor->param_flag = 2;
	}
	else if (check_position(mouse_position, editor->menu.s_cb_coord))
	{
		editor->param_flag = 3;
	}
	else
		check_emenu_cursor2(editor, mouse_position);
}
