/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ques_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:05:44 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/30 15:05:46 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	close_ques_win(t_editor *editor)
{
	SDL_FreeSurface(editor->ques_surf);
	SDL_DestroyWindow(editor->ques_win);
	editor->ques_win = NULL;
}

void	set_ques_flag(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.yes_button))
		editor->ques_flag = 1;
	else if (check_position(mouse_position, editor->menu.no_button))
		editor->ques_flag = 2;
	else
		editor->ques_flag = 0;
}

void	ques_event(t_editor *editor, SDL_Event event, t_coords mouse_position)
{
	set_ques_flag(editor, mouse_position);
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		close_ques_win(editor);
		return ;
	}

	if (editor->ques_flag == 1)
	{
		SDL_BlitScaled(editor->button[9], NULL, editor->ques_surf, &editor->menu.rect1);
		SDL_BlitScaled(editor->button[8], NULL, editor->ques_surf, &editor->menu.rect2);
	}
	else if (editor->ques_flag == 2)
	{
		SDL_BlitScaled(editor->button[9], NULL, editor->ques_surf, &editor->menu.rect2);
		SDL_BlitScaled(editor->button[8], NULL, editor->ques_surf, &editor->menu.rect1);
	}
	else
	{
		SDL_BlitScaled(editor->button[8], NULL, editor->ques_surf, &editor->menu.rect2);
		SDL_BlitScaled(editor->button[8], NULL, editor->ques_surf, &editor->menu.rect1);
	}
	if (editor->ques_flag == 1 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		editor->flags.t_f.rewrite = 1;
		SDL_BlitScaled(editor->button[10], NULL, editor->ques_surf, &editor->menu.rect1);
		close_ques_win(editor);
		return ;
	}
	else if (editor->ques_flag == 2 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_BlitScaled(editor->button[10], NULL, editor->ques_surf, &editor->menu.rect2);
		editor->flags.t_f.rewrite = 0;
		close_ques_win(editor);
		return ;
	}
}

void	ques_win_init(t_editor *editor)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	color = (SDL_Color){0, 0, 0, 0};
	f.x = editor->menu.yes_button.x + 20;
	f.y = editor->menu.yes_button.y + 10;
	message = TTF_RenderText_Solid(editor->font1, "Yes", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->ques_win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.no_button.x + 20;
	f.y = editor->menu.no_button.y + 10;
	message = TTF_RenderText_Solid(editor->font1, "NO", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->ques_win), &f);
	SDL_FreeSurface(message);
	editor->menu.rect1.x = editor->menu.yes_button.x;
	editor->menu.rect1.y = editor->menu.yes_button.y;
	editor->menu.rect1.w = 96;
	editor->menu.rect1.h = 32;
	editor->menu.rect2.x = editor->menu.no_button.x;
	editor->menu.rect2.y = editor->menu.no_button.y;
	editor->menu.rect2.w = 96;
	editor->menu.rect2.h = 32;
}

int		ques_win(t_editor *editor, SDL_Event event)
{
	t_coords 	mouse_position;

	editor->ques_win = SDL_CreateWindow("Save map",\
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 240, 100, 0);
	editor->ques_surf = SDL_GetWindowSurface(editor->ques_win);
	while (1)
	{
		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		ques_win_init(editor);
		while (SDL_PollEvent(&event))
			ques_event(editor, event, mouse_position);
		if (!editor->ques_win)
			break ;
		SDL_UpdateWindowSurface(editor->ques_win);
	}
	return (editor->flags.t_f.rewrite);
}
