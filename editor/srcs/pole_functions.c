/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pole_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:46:31 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/24 19:46:33 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		draw_caption(t_editor *editor, t_coord coord,\
	SDL_Window *win, t_capt caption)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	f.x = coord.x - caption.delim;
	f.y = coord.y + 5;
	color = (SDL_Color){0, 0, 0, 0};
	message = TTF_RenderText_Solid(editor->font1, caption.caption, color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(win), &f);
	SDL_FreeSurface(message);
}

void		add_text_to_space(t_editor *editor, t_coord coord,\
	SDL_Window *win, char *text)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	f.x = coord.x + 5;
	f.y = coord.y + 5;
	color = (SDL_Color){0, 0, 0, 0};
	message = TTF_RenderText_Solid(editor->font1, text, color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(win), &f);
	SDL_FreeSurface(message);
}

void		write_to_second_pole(t_editor *editor)
{
	ft_strdel(&editor->new_win->height_above);
	editor->new_win->height_above =\
	ft_itoa(editor->new_win->param_par.line->begin_height);
	add_text_to_space(editor, editor->new_win->ws_coord2,\
	editor->new_win->win, editor->new_win->height_above);
}

void		write_to_first_pole(t_editor *editor)
{
	if (editor->new_win->param_flag == 1)
	{
		ft_strdel(&editor->new_win->height_wall);
		editor->new_win->height_wall =\
		ft_itoa(editor->new_win->param_par.line->height);
		add_text_to_space(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, editor->new_win->height_wall);
	}
	if (editor->new_win->param_flag == 2)
	{
		ft_strdel(&editor->new_win->f_height);
		editor->new_win->f_height =\
		ft_itoa(editor->new_win->param_par.room->f_height);
		add_text_to_space(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, editor->new_win->f_height);
	}
	if (editor->new_win->param_flag == 3)
	{
		ft_strdel(&editor->new_win->s_height);
		editor->new_win->s_height =\
		ft_itoa(editor->new_win->param_par.sprite->s_height);
		add_text_to_space(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, editor->new_win->s_height);
	}
}

void		write_text_to_pole(t_editor *editor)
{
	write_to_first_pole(editor);
	if (editor->new_win->param_flag == 1)
		write_to_second_pole(editor);
}
