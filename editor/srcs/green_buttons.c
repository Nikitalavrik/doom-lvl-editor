/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   green_buttons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:48:55 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/26 17:48:56 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	draw_emenu_big_buttons2(t_editor *editor, SDL_Rect rect1)
{
	rect1.x = editor->menu.load_butt.x;
	rect1.y = editor->menu.load_butt.y;
	if (editor->flags.t_f.load_b == 1)
		SDL_BlitScaled(editor->button[10], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.load_b == 0 && editor->param_flag == 9)
		SDL_BlitScaled(editor->button[9], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[8], NULL, editor->surf, &rect1);
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
	draw_emenu_big_buttons2(editor, rect1);
}

void	draw_emenu_help_buttons2(t_editor *editor, SDL_Rect rect1)
{
	rect1.x = editor->menu.select_b.x;
	rect1.y = editor->menu.select_b.y;
	if (editor->flags.t_f.bselect == 1)
		SDL_BlitScaled(editor->button[6], NULL, editor->surf, &rect1);
	else if (editor->flags.t_f.bselect == 0 && editor->param_flag == 11)
		SDL_BlitScaled(editor->button[5], NULL, editor->surf, &rect1);
	else
		SDL_BlitScaled(editor->button[7], NULL, editor->surf, &rect1);
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
	draw_emenu_help_buttons2(editor, rect1);
}
