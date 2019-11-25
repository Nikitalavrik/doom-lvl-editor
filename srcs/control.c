/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/25 10:39:18 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	move_player(t_doom *doom)
{
	if (doom->event.type == SDL_KEYDOWN || doom->event.type == SDL_KEYUP)
	{
		if (doom->event.key.keysym.sym == 'w')
			doom->move.wsad[0] = doom->event.type == SDL_KEYDOWN;
		else if (doom->event.key.keysym.sym == 's')
			doom->move.wsad[1] = doom->event.type == SDL_KEYDOWN;
		else if (doom->event.key.keysym.sym == 'a')
			doom->move.wsad[2] = doom->event.type == SDL_KEYDOWN;
		else if (doom->event.key.keysym.sym == 'd')
			doom->move.wsad[3] = doom->event.type == SDL_KEYDOWN;
		if (doom->move.wsad[0])
		{
			doom->play[0].t.z += SDL_cos(doom->play[0].angle_y * PI / 180) * doom->play[0].speed;
			doom->play[0].t.x -= SDL_sin(doom->play[0].angle_y * PI / 180) * doom->play[0].speed;
			doom->play[0].t.y -= doom->play[0].angle_x / 240;
		}
	}
}


int		detect_event(t_editor *editor)
{
	t_coords 	mouse_position;
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (!editor->flags.t_f.visual)
		{
			if (event.type == SDL_MOUSEWHEEL)
				mouse_event(editor, event);
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				editor->flags.t_f.move = editor->flags.t_f.select;
				editor->move_save.x = mouse_position.x;
				editor->move_save.y = mouse_position.y;
				check_rooms(editor, mouse_position, 1);
				if (editor->flags.t_f.sprite && editor->selected)
					add_sprite(editor);
				if (!editor->flags.t_f.select && !editor->flags.t_f.sprite)
					add_line(editor);
			}
			if (event.button.clicks == 1 && event.button.button == SDL_BUTTON_RIGHT)
			{
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				if (check_line(editor, mouse_position))
					choice_win(editor, event, 1);
			}
			if (event.type == SDL_MOUSEBUTTONUP && editor->flags.t_f.move)
				editor->flags.t_f.move = 0;
			if (editor->flags.t_f.move)
				mouse_move(editor);
			if (event.type == SDL_MOUSEMOTION)
				mouse_motion(editor);

		}
		else
		{
			editor->doom->event = event;
			move_player(editor->doom);
			SDL_GetRelativeMouseState(&editor->doom->mouse.x,&editor->doom->mouse.y);
			editor->doom->play[0].angle_x += editor->doom->mouse.y;
			editor->doom->play[0].angle_y -= editor->doom->mouse.x * DELTA;
			if (editor->doom->play[0].angle_y >= 360.0)
				editor->doom->play[0].angle_y -= 360.0;
			else if (editor->doom->play[0].angle_y < 0)
				editor->doom->play[0].angle_y += 360.0;
			if (editor->doom->play[0].angle_x > editor->doom->skybox.indent)
				editor->doom->play[0].angle_x = editor->doom->skybox.indent;
			else if (editor->doom->play[0].angle_x < -editor->doom->skybox.indent)
				editor->doom->play[0].angle_x = -editor->doom->skybox.indent;
		}
		if (event.type == SDL_KEYDOWN)
			if (keyboard_events_down(editor, event))
				return (1);
		if (event.type == SDL_KEYUP)
			if (keyboard_events_up(editor, event))
				return (1);
	}
	return (0);
}
