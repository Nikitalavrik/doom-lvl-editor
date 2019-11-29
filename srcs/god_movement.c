/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:12:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 16:14:58 by nlavrine         ###   ########.fr       */
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

void	god_rot_move(t_editor *editor, SDL_Event event)
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
