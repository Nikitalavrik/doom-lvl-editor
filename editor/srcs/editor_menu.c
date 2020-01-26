/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:37:14 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/26 15:20:45 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	draw_emenu_check_buttons2(t_editor *editor, SDL_Rect rect1)
{
	rect1.x = editor->menu.del_cb_coord.x;
	rect1.y = editor->menu.del_cb_coord.y;
	SDL_BlitScaled(editor->button[editor->flags.t_f.d_butt ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.first_floor.x;
	rect1.y = editor->menu.first_floor.y;
	SDL_BlitScaled(editor->button[editor->flags.t_f.f_floor ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.second_floor.x;
	rect1.y = editor->menu.second_floor.y;
	SDL_BlitScaled(editor->button[editor->flags.t_f.s_floor ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.third_floor.x;
	rect1.y = editor->menu.third_floor.y;
	SDL_BlitScaled(editor->button[editor->flags.t_f.t_floor ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
}

void	draw_emenu_check_buttons(t_editor *editor)
{
	SDL_Rect	rect1;

	rect1.x = editor->menu.f_cb_coord.x;
	rect1.y = editor->menu.f_cb_coord.y;
	rect1.w = 16;
	rect1.h = 16;
	SDL_BlitScaled(editor->button[editor->flags.t_f.f_butt ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.s_cb_coord.x;
	rect1.y = editor->menu.s_cb_coord.y;
	SDL_BlitScaled(editor->button[editor->flags.t_f.s_butt ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.t_cb_coord.x;
	rect1.y = editor->menu.t_cb_coord.y;
	SDL_BlitScaled(editor->button[editor->flags.t_f.t_butt ==\
		1 ? 4 : 3], NULL, editor->surf, &rect1);
	draw_emenu_check_buttons2(editor, rect1);
}

void	create_pole_to_save_name(t_editor *editor)
{
	char *num;

	editor->menu.coord.x = editor->width - MENU_WIDTH + 100;
	editor->menu.coord.y = 20;
	editor->menu.coord.x1 = editor->width - 20;
	editor->menu.coord.y1 = editor->menu.coord.y + 20;
	editor->menu.caption.caption = "Map name :";
	editor->menu.caption.delim = 90;
	draw_white_space(editor->menu.coord, editor->surf,\
		editor->flags.t_f.m_pole == 1 ? ACT_BACK : BACKGROUND);
	draw_caption(editor, editor->menu.coord, editor->win, editor->menu.caption);
	if (editor->filename == NULL)
	{
		num = ft_itoa((unsigned short int)&editor->doom);
		editor->filename = ft_strdup(num);
		ft_memdel((void **)&num);
	}
	add_text_to_space(editor, editor->menu.coord,\
		editor->win, editor->filename);
}

void	draw_menu_background(t_editor *editor)
{
	int x;
	int y;

	x = editor->width - MENU_WIDTH;
	while (x < editor->width)
	{
		y = 0;
		while (y < editor->height)
		{
			if (x >= 0 && y >= 0 && y < editor->height)
				((int *)editor->surf->pixels)\
			[(y * editor->surf->w) + x] = 0xcccccc;
			y++;
		}
		x++;
	}
}

void	draw_editor_menu(t_editor *editor)
{
	draw_menu_background(editor);
	create_pole_to_save_name(editor);
	draw_emenu_check_buttons(editor);
	draw_emenu_help_buttons(editor);
	draw_emenu_big_buttons(editor);
	write_button_name(editor);
	check_emenu_pole(editor);
}
