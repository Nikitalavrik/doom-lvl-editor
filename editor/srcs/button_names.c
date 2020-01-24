/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_names.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:33:44 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/23 16:33:45 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	write_button_name4(t_editor *editor, SDL_Rect f,\
	SDL_Surface *message, SDL_Color color)
{
	f.x = editor->menu.load_butt.x + 112;
	f.y = editor->menu.load_butt.y + 8;
	message = TTF_RenderText_Solid(editor->font1, "Load map", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
}

void	write_button_name3(t_editor *editor, SDL_Rect f,\
	SDL_Surface *message, SDL_Color color)
{
	f.y = editor->menu.second_floor.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Second floor level", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = editor->menu.third_floor.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Third floor level", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = editor->menu.clear_lvl.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Clear lvl", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.return_butt.x + 100;
	f.y = editor->menu.return_butt.y + 8;
	message = TTF_RenderText_Solid(editor->font1, "Back to menu", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.save_butt.x + 112;
	f.y = editor->menu.save_butt.y + 8;
	message = TTF_RenderText_Solid(editor->font1, "Save map", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	write_button_name4(editor, f, message, color);
}

void	write_button_name2(t_editor *editor, SDL_Rect f,\
	SDL_Surface *message, SDL_Color color)
{
	f.y = editor->menu.del_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Delete", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.clo_cb_coord.x + 30;
	f.y = editor->menu.clo_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Close room", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = editor->menu.select_b.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Select", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.first_floor.x + 30;
	f.y = editor->menu.first_floor.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "First floor level", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = 200 + 2;
	message = TTF_RenderText_Solid(editor->font1,\
	"------------------- Select floor lvl --------------------", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	write_button_name3(editor, f, message, color);
}

void	write_button_name(t_editor *editor)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	color = (SDL_Color){0, 0, 0, 0};
	f.x = editor->menu.f_cb_coord.x + 30;
	f.y = 50 + 2;
	message = TTF_RenderText_Solid(editor->font1,\
	"----------------------------- Draw ------------------------------",\
	color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = editor->menu.f_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Draw wall", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = editor->menu.s_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Draw floor", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	f.y = editor->menu.t_cb_coord.y + 2;
	message = TTF_RenderText_Solid(editor->font1, "Draw sprite", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->win), &f);
	SDL_FreeSurface(message);
	write_button_name2(editor, f, message, color);
}
