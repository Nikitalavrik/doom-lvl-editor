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

void	ques_button_names2(t_editor *editor)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	color = (SDL_Color){0, 0, 0, 0};
	f.x = 30;
	f.y = 10;
	message = TTF_RenderText_Solid(editor->font1,\
		"This filename already exist.", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->ques_win), &f);
	SDL_FreeSurface(message);
	f.x = 18;
	f.y = 25;
	message = TTF_RenderText_Solid(editor->font1,\
		"Do you want to rewrite this file?", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->ques_win), &f);
	f.x = 30;
	f.y = 40;
	message = TTF_RenderText_Solid(editor->font1,\
		"Click \"Yes\" to rewrite the file.", color);
	SDL_BlitSurface(message, NULL, SDL_GetWindowSurface(editor->ques_win), &f);
	SDL_FreeSurface(message);
}

void	ques_button_names(t_editor *editor)
{
	SDL_Color	color;
	SDL_Surface	*message;
	SDL_Rect	f;

	color = (SDL_Color){0, 0, 0, 0};
	f.x = editor->menu.yes_button.x + 40;
	f.y = editor->menu.yes_button.y + 10;
	message = TTF_RenderText_Solid(editor->font1, "Yes", color);
	SDL_BlitSurface(message, NULL,\
		SDL_GetWindowSurface(editor->ques_win), &f);
	SDL_FreeSurface(message);
	f.x = editor->menu.no_button.x + 40;
	f.y = editor->menu.no_button.y + 10;
	message = TTF_RenderText_Solid(editor->font1, "NO", color);
	SDL_BlitSurface(message, NULL,\
		SDL_GetWindowSurface(editor->ques_win), &f);
	SDL_FreeSurface(message);
	ques_button_names2(editor);
}

void	draw_ques_background(t_editor *editor)
{
	int x;
	int y;

	x = 0;
	while (x < 240)
	{
		y = 0;
		while (y < 100)
		{
			if (x >= 0 && y >= 0 && y < 100)
				((int *)editor->ques_surf->pixels)\
			[(y * editor->ques_surf->w) + x] = 0xcccccc;
			y++;
		}
		x++;
	}
}

void	ques_init(t_editor *editor)
{
	editor->ques_win = SDL_CreateWindow("Save map",\
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 240, 100, 0);
	editor->ques_surf = SDL_GetWindowSurface(editor->ques_win);
	draw_ques_background(editor);
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
	t_coords	mouse_position;

	ques_init(editor);
	while (1)
	{
		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		while (SDL_PollEvent(&event))
			ques_event(editor, event, mouse_position);
		if (!editor->ques_win)
			break ;
		SDL_UpdateWindowSurface(editor->ques_win);
	}
	return (editor->flags.t_f.rewrite);
}
