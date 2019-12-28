/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_rectangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:03:53 by tbratsla          #+#    #+#             */
/*   Updated: 2019/12/23 17:03:54 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		cicles_of_rect(t_editor *editor, int n, t_coord coord, Uint32 color)
{
	int i;

	i = coord.x - n;
	while (i < coord.x1 + n)
	{
		put_to_screen(editor, i, coord.y - n, color);
		put_to_screen(editor, i, coord.y1 + n, color);
		i++;
	}
	i = editor->new_win->active_num.coord.y - n;
	while (i <= editor->new_win->active_num.coord.y1 + n)
	{
		put_to_screen(editor, coord.x - n, i, color);
		put_to_screen(editor, coord.x1 + n, i, color);
		i++;
	}
}

t_coord		get_coord(t_editor *editor)
{
	t_coord	coord;

	coord.x = (editor->new_win->mouse.x / 148 * 148 + 20);
	coord.x1 = coord.x + 128;
	coord.y = ((editor->new_win->mouse.y + editor->new_win->cam_y)\
		/ 148 * 148 + 20);
	coord.y1 = coord.y + 128;
	editor->new_win->active_num.tex_num = editor->new_win->mouse.x / 148 +\
	(editor->new_win->mouse.y + editor->new_win->cam_y) / 148 * C_WIDTH / 148;
	editor->new_win->active_num.coord.x = coord.x;
	editor->new_win->active_num.coord.y = coord.y;
	editor->new_win->active_num.coord.x1 = coord.x1;
	editor->new_win->active_num.coord.y1 = coord.y1;
	return (coord);
}

void		remove_rectangle(t_editor *editor)
{
	int		n;

	n = 10;
	while (n > 0)
	{
		cicles_of_rect(editor, n,\
		editor->new_win->active_num.coord, 0x000000);
		n--;
	}
	draw_list_text(editor);
}

void		draw_rectangle(t_editor *editor)
{
	t_coord	coord;
	int		n;

	n = 10;
	if (editor->new_win->active_num.tex_num > -1)
		remove_rectangle(editor);
	coord = get_coord(editor);
	while (n > 0)
	{
		cicles_of_rect(editor, n, coord, 0x0062ff);
		n--;
	}
	draw_list_text(editor);
}

void		draw_first_rectangle(t_editor *editor)
{
	int		n;

	n = 10;
	while (n > 0)
	{
		cicles_of_rect(editor, n,\
		editor->new_win->active_num.coord, 0x0062ff);
		n--;
	}
}
