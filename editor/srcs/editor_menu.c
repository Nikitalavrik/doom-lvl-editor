/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:37:14 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/26 13:19:39 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	check_emenu_pole(t_editor *editor)
{
	if (editor->flags.t_f.f_butt == 1)
		switch_to_line_build(editor);
	if (editor->flags.t_f.s_butt == 1 && !editor->flags.t_f.floor)
		switch_to_floor_build(editor);
	if (editor->flags.t_f.t_butt == 1 && editor->selected)
		switch_to_sprite_put(editor);
	if (editor->flags.t_f.d_butt == 1 && editor->flags.t_f.select == 1)
		find_and_delete(editor);
	if (editor->flags.t_f.c_butt == 1 && editor->point)
		close_room(editor);
	if (editor->flags.t_f.f_floor == 1)
		editor->floor = 1;
	else if (editor->flags.t_f.s_floor == 1)
		editor->floor = 2;
	else if (editor->flags.t_f.t_floor == 1)
		editor->floor = 3;
	if (editor->flags.t_f.save_b == 1)
	{
		d3_init(editor);
		editor->flags.t_f.visual = 0;
	}
	if (editor->flags.t_f.load_b == 1)
	{
		load_to_editor(editor, editor->filename);
	}
	if (editor->flags.t_f.bselect == 1)
		editor->flags.t_f.select = 1;
	null_buttons(editor);
}

void	draw_emenu_big_buttons(t_editor *editor)
{
	SDL_Rect	rect1;

	rect1.x = editor->menu.return_butt.x;
	rect1.y = editor->menu.return_butt.y;
	rect1.w = 280;
	rect1.h = 32;
	if (editor->flags.t_f.ret_b == 1)
		SDL_BlitScaled(editor->button[10], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.ret_b == 0 && editor->param_flag == 7)
		SDL_BlitScaled(editor->button[9], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[8], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.save_butt.x;
	rect1.y = editor->menu.save_butt.y;
	if (editor->flags.t_f.save_b == 1)
		SDL_BlitScaled(editor->button[10], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.save_b == 0 && editor->param_flag == 8)
		SDL_BlitScaled(editor->button[9], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[8], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.load_butt.x;
	rect1.y = editor->menu.load_butt.y;
	if (editor->flags.t_f.load_b == 1)
		SDL_BlitScaled(editor->button[10], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.load_b == 0 && editor->param_flag == 9)
		SDL_BlitScaled(editor->button[9], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[8], NULL, editor->surf, &rect1);
}

void	draw_emenu_help_buttons(t_editor *editor)
{
	SDL_Rect	rect1;

	rect1.w = 16;
	rect1.h = 16;
	rect1.x = editor->menu.clo_cb_coord.x;
	rect1.y = editor->menu.clo_cb_coord.y;
	if (editor->flags.t_f.c_butt == 1)
		SDL_BlitScaled(editor->button[6], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.c_butt == 0 && editor->param_flag == 6)
		SDL_BlitScaled(editor->button[5], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[7], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.clear_lvl.x;
	rect1.y = editor->menu.clear_lvl.y;
	if (editor->flags.t_f.clear_b == 1)
	{
		SDL_BlitScaled(editor->button[6], NULL, editor->surf, &rect1);
	}
	else if (editor->flags.t_f.clear_b == 0 && editor->param_flag == 10)
		SDL_BlitScaled(editor->button[5], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[7], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.select_b.x;
	rect1.y = editor->menu.select_b.y;
	if (editor->flags.t_f.bselect == 1)
		SDL_BlitScaled(editor->button[6], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.bselect == 0 && editor->param_flag == 11)
		SDL_BlitScaled(editor->button[5], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[7], NULL, editor->surf, &rect1);
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
	// ft_printf("draw me\n");
}
