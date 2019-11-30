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
			editor->new_win->cam_y += 50;
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
	if(event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y > 0)
		{
			if (editor->new_win->cam_y < editor->new_win->mem_space - C_HEIGHT - 35)
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
		SDL_FreeSurface(editor->new_win->sur);
		SDL_DestroyWindow(SDL_GetWindowFromID(editor->new_win->win_id));
		free(editor->new_win);
		editor->new_win = NULL;
		SDL_StopTextInput();
		return ;
	}
	if (event.button.clicks == 1)
	{
		SDL_GetMouseState(&editor->new_win->mouse.x, &editor->new_win->mouse.y);
		if ((editor->new_win->mouse.x % editor->new_win->delim_x) > 20 &&\
			editor->new_win->mouse.x < C_WIDTH - 20 &&\
			((editor->new_win->mouse.y + editor->new_win->cam_y) %\
			editor->new_win->delim_y) > 20 && (editor->new_win->mouse.y +\
			editor->new_win->cam_y) < editor->new_win->mem_space)
			draw_rectangle(editor);
		get_pole_num(editor);
	}
	else if ((event.type == SDL_TEXTINPUT || event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_1)
		write_to_pole(editor, &editor->new_win->wall_angle, event);
	else if ((event.type == SDL_TEXTINPUT || event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_2)
		write_to_pole(editor, &editor->new_win->height_wall, event);
	else if ((event.type == SDL_TEXTINPUT || event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_3)
		write_to_pole(editor, &editor->new_win->height_above, event);
	else if ((event.type == SDL_TEXTINPUT || event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_4)
		write_to_pole(editor, &editor->new_win->transp, event);
	new_event2(editor, event);
}
