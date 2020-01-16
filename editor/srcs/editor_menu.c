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

void	check_emenu_pole(t_editor *editor)
{
	if (editor->flags.t_f.f_butt == 1)
		switch_to_line_build(editor);
	if (editor->flags.t_f.s_butt == 1)
		switch_to_floor_build(editor);
	if (editor->flags.t_f.t_butt == 1 && editor->selected)
		switch_to_sprite_put(editor);
}

void	init_emenu_buttons(t_editor *editor)
{
	editor->menu.f_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.f_cb_coord.x1 = editor->menu.f_cb_coord.x + 16;
	editor->menu.f_cb_coord.y = 70;
	editor->menu.f_cb_coord.y1 = editor->menu.f_cb_coord.y + 16;
	editor->menu.s_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.s_cb_coord.x1 = editor->menu.s_cb_coord.x + 16;
	editor->menu.s_cb_coord.y = 100;
	editor->menu.s_cb_coord.y1 = editor->menu.s_cb_coord.y + 16;
	editor->menu.t_cb_coord.x = editor->width - MENU_WIDTH + 10;
	editor->menu.t_cb_coord.x1 = editor->menu.t_cb_coord.x + 16;
	editor->menu.t_cb_coord.y = 130;
	editor->menu.t_cb_coord.y1 = editor->menu.t_cb_coord.y + 16;

}

void	write_button_name(t_editor *editor)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	color = (SDL_Color){0, 0, 0, 0};
	f.x = editor->menu.f_cb_coord.x + 30;
	f.y = editor->menu.f_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Draw wall", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.s_cb_coord.x + 30;
	f.y = editor->menu.s_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Draw floor", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.t_cb_coord.x + 30;
	f.y = editor->menu.t_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Draw sprite", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
}

void	draw_emenu_check_buttons(t_editor *editor)
{
	SDL_Rect	rect1;

	rect1.x = editor->menu.f_cb_coord.x;
	rect1.y = editor->menu.f_cb_coord.y;
	rect1.w = 16;
	rect1.h = 16;
	SDL_BlitScaled(editor->button[editor->flags.t_f.f_butt == 1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.s_cb_coord.x;
	rect1.y = editor->menu.s_cb_coord.y;
	rect1.w = 16;
	rect1.h = 16;
	SDL_BlitScaled(editor->button[editor->flags.t_f.s_butt == 1 ? 4 : 3], NULL, editor->surf, &rect1);
	rect1.x = editor->menu.t_cb_coord.x;
	rect1.y = editor->menu.t_cb_coord.y;
	rect1.w = 16;
	rect1.h = 16;
	SDL_BlitScaled(editor->button[editor->flags.t_f.t_butt == 1 ? 4 : 3], NULL, editor->surf, &rect1);
	write_button_name(editor);
	
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
	draw_white_space(editor->menu.coord, editor->surf, editor->flags.t_f.m_pole == 1 ? ACT_BACK : BACKGROUND);
	draw_caption(editor, editor->menu.coord, editor->win, editor->menu.caption);
	if (editor->filename == NULL)
	{
		num = ft_itoa((unsigned short int)&editor->doom);
		editor->filename = ft_strdup(num);
		ft_memdel((void **)&num);
	}
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
	draw_emenu_check_buttons(editor);
	check_emenu_pole(editor);


}
