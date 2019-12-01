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

int			check_currsor(t_editor *editor)
{
	if (editor->new_win->mouse.x > editor->new_win->button_coord.x &&\
		editor->new_win->mouse.x < editor->new_win->button_coord.x1 &&\
		editor->new_win->mouse.y > editor->new_win->button_coord.y &&\
		editor->new_win->mouse.y < editor->new_win->button_coord.y1)
		return (1);
	return (0);
}

void		close_choice_win(t_editor *editor)
{
	t_eline	*line;
	int		i;

	line = (t_eline *)editor->new_win->param;
	line->rot_angle = ft_atoi(editor->new_win->wall_angle);
	line->height = ft_atoi(editor->new_win->height_wall);
	line->begin_height = ft_atoi(editor->new_win->height_above);
	line->alpha = ft_atoi(editor->new_win->transp);
	line->num_of_textures = (editor->new_win->active_num.tex_num + 1) % editor->doom->count_text;
	if (!line->num_of_textures)
		line->num_of_textures++;
	free(editor->new_win->wall_angle);
	free(editor->new_win->height_wall);
	free(editor->new_win->height_above);
	free(editor->new_win->transp);
	i = 0;
	while (i < editor->new_win->mem_space)
	{
		free(editor->new_win->screen[i]);
		i++;
	}
	free(editor->new_win->screen);
	free(editor->new_win->events);
	SDL_FreeSurface(editor->new_win->sur);
	SDL_DestroyWindow(SDL_GetWindowFromID(editor->new_win->win_id));
	free(editor->new_win);
	editor->new_win = NULL;
	SDL_StopTextInput();
}

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
		close_choice_win(editor);
		return ;
	}
	else
	{
		if(editor->new_win)
		{
			SDL_GetMouseState(&editor->new_win->mouse.x, &editor->new_win->mouse.y);
		
			if (check_currsor(editor) == 1 && event.button.type != SDL_MOUSEBUTTONDOWN)
				draw_button(editor, 0);
			else if (check_currsor(editor) == 1 && event.button.type == SDL_MOUSEBUTTONDOWN)
				draw_button(editor, 2);
			else
				draw_button(editor, 1);
			if (check_currsor(editor) == 1 && event.button.type == SDL_MOUSEBUTTONUP)
			{
				close_choice_win(editor);
				return ;
			}
			if (event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
			{
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
	}
}
