/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:33:54 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/22 19:33:56 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		new_event4(t_editor *editor, SDL_Event event)
{
	if (editor->new_win->events->up)
	{
		if (editor->new_win->cam_y > 50)
			editor->new_win->cam_y -= 50;
		else
			editor->new_win->cam_y = 0;
		draw_list_text(editor);
		SDL_UpdateWindowSurface(editor->new_win->win);
		editor->new_win->events->down = 0;
	}
	event.button.clicks = event.button.clicks + 1 - 1;
}

void		new_event3(t_editor *editor, SDL_Event event)
{
	if ((event.key.keysym.sym == SDLK_w ||\
			event.key.keysym.sym == SDLK_UP))
		editor->new_win->events->up = event.key.type == SDL_KEYDOWN;
	if ((event.key.keysym.sym == SDLK_s ||\
		event.key.keysym.sym == SDLK_DOWN))
		editor->new_win->events->down = event.key.type == SDL_KEYDOWN;
	if (editor->new_win->events->down)
	{
		if (editor->new_win->cam_y < editor->new_win->mem_space - C_HEIGHT - 35)
			editor->new_win->cam_y += 35;
		else
			editor->new_win->cam_y = editor->new_win->mem_space - C_HEIGHT;
		draw_list_text(editor);
		SDL_UpdateWindowSurface(editor->new_win->win);
		editor->new_win->events->up = 0;
	}
	new_event4(editor, event);
}

void		new_event2(t_editor *editor, SDL_Event event)
{
	if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y > 0)
		{
			if (editor->new_win->cam_y <\
				editor->new_win->mem_space - C_HEIGHT - 35)
				editor->new_win->cam_y += 35;
			else
				editor->new_win->cam_y = editor->new_win->mem_space - C_HEIGHT;
			draw_list_text(editor);
		}
		if (event.wheel.y < 0)
		{
			if (editor->new_win->cam_y > 35)
				editor->new_win->cam_y -= 35;
			else
				editor->new_win->cam_y = 0;
			draw_list_text(editor);
		}
	}
	if (event.key.type == SDL_KEYDOWN ||\
		event.key.type == SDL_KEYUP)
		new_event3(editor, event);
}

void		new_event(t_editor *editor, SDL_Event event)
{
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		close_choice_win(editor);
		return ;
	}
	else if (editor->new_win)
	{
		SDL_GetMouseState(&editor->new_win->mouse.x, &editor->new_win->mouse.y);
		set_new_win_button_texture(editor, event);
		if (check_currsor(editor) == 1 &&\
			event.button.type == SDL_MOUSEBUTTONUP)
		{
			save_parametrs(editor);
			close_choice_win(editor);
			return ;
		}
		if (event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
			get_nw_act_pole(editor);
		set_nw_param(editor, event);
		new_event2(editor, event);
	}
}
