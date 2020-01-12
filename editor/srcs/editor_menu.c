/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:37:14 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/12 14:37:16 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	create_pole_to_save_name(t_editor *editor)
{
	editor->menu.coord.x = editor->width - MENU_WIDTH + 100;
	editor->menu.coord.y = 20;
	editor->menu.coord.x1 = editor->width - 20;
	editor->menu.coord.y1 = editor->menu.coord.y + 20;
	editor->menu.caption.caption = "Map name :";
	editor->menu.caption.delim = 90;
	draw_white_space(editor->menu.coord, editor->surf, BACKGROUND);
	draw_caption(editor, editor->menu.coord, editor->win, editor->menu.caption);
	add_text_to_space(editor, editor->menu.coord, editor->win, editor->filename);
}

void	draw_menu_background(t_editor *editor)
{
	int x;
	int y;

	x = editor->width - MENU_WIDTH;
	while (x < editor->width)
	{
		y = 0;
		while(y < editor->height)
		{
			if (x >= 0 && y >= 0 && y < editor->height)
				((int *)editor->surf->pixels)[(y * editor->surf->w) + x] = 0xcccccc;
			y++;
		}
		x++;
	}
}

void	draw_editor_menu(t_editor *editor)
{
	draw_menu_background(editor);
	create_pole_to_save_name(editor);

}
