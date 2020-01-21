/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_nw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:01:10 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 18:01:11 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int			check_currsor(t_editor *editor)
{
	if (editor->new_win->mouse.x > editor->new_win->button_coord.x &&\
		editor->new_win->mouse.x < editor->new_win->button_coord.x1 &&\
		editor->new_win->mouse.y > editor->new_win->button_coord.y &&\
		editor->new_win->mouse.y < editor->new_win->button_coord.y1)
		return (1);
	return (0);
}

void		set_new_win_button_texture(t_editor *editor, SDL_Event event)
{
	if (check_currsor(editor) == 1 &&\
		event.button.type != SDL_MOUSEBUTTONDOWN)
		draw_button(editor, 0);
	else if (check_currsor(editor) == 1\
		&& event.button.type == SDL_MOUSEBUTTONDOWN)
		draw_button(editor, 2);
	else
		draw_button(editor, 1);
}

void		draw_button(t_editor *editor, int button_num)
{
	SDL_Rect	rect1;
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	rect1.x = editor->new_win->button_coord.x;
	rect1.y = editor->new_win->button_coord.y;
	rect1.w = editor->new_win->button_coord.x1 -\
	editor->new_win->button_coord.x;
	rect1.h = editor->new_win->button_coord.y1 -\
	editor->new_win->button_coord.y;
	SDL_BlitScaled(editor->button[button_num],\
		NULL, editor->new_win->sur, &rect1);
	f.x = rect1.x + 95;
	f.y = rect1.y + 10;
	color = (SDL_Color){200, 200, 100, 0};
	message = TTF_RenderText_Solid(editor->font1, "SAVE AND EXIT", color);
	SDL_BlitSurface(message, NULL,\
		SDL_GetWindowSurface(editor->new_win->win), &f);
	SDL_FreeSurface(message);
	SDL_UpdateWindowSurface(editor->new_win->win);
}
