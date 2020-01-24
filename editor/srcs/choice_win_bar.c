/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_win_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:29:33 by tbratsla          #+#    #+#             */
/*   Updated: 2019/12/28 17:45:35 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		draw_background(t_editor *editor)
{
	int		x;
	int		y;
	Uint32	*pic;

	x = C_WIDTH;
	while (x < 1024)
	{
		y = 0;
		while (y < C_HEIGHT)
		{
			pic = editor->new_win->sur->pixels + y *\
			editor->new_win->sur->pitch + x *\
			editor->new_win->sur->format->BytesPerPixel;
			*pic = 0xcccccc;
			y++;
		}
		x++;
	}
}

t_coord		get_input_coord(int x, int y)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	coord.x1 = x + 80;
	coord.y1 = y + 20;
	return (coord);
}

void		draw_white_space(t_coord coord, SDL_Surface *surf, Uint32 color)
{
	int		y;
	Uint32	*pic;

	y = coord.y;
	while (coord.x < coord.x1)
	{
		coord.y = y;
		while (coord.y < coord.y1)
		{
			pic = surf->pixels + coord.y * surf->pitch +
			coord.x * surf->format->BytesPerPixel;
			*pic = color;
			coord.y++;
		}
		coord.x++;
	}
}

void		draw_right_menu(t_editor *editor)
{
	t_capt caption;

	caption.delim = 190;
	draw_background(editor);
	draw_white_space(editor->new_win->ws_coord1,\
		editor->new_win->sur, BACKGROUND);
	if (editor->new_win->param_flag == 1)
	{
		caption.caption = "Height the wall:";
		draw_caption(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, caption);
		caption.caption = "Height wall above the floor:";
		draw_caption(editor, editor->new_win->ws_coord2,\
		editor->new_win->win, caption);
		draw_white_space(editor->new_win->ws_coord2,\
		editor->new_win->sur, BACKGROUND);
	}
	if (editor->new_win->param_flag == 2 || editor->new_win->param_flag == 3)
	{
		caption.caption = "Height:";
		draw_caption(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, caption);
	}
	write_text_to_pole(editor);
}
