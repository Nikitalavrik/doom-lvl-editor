/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:12:18 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/12 12:58:20 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	calc_movement(t_doom *doom)
{
	t_dcoords	step;

	step.x = SDL_cos(doom->play[0].angle_y * PI / 180);
	step.y = SDL_sin(doom->play[0].angle_y * PI / 180);
	if (doom->move.wsad[0])
	{
		doom->play[0].t.z += step.x * doom->play[0].speed;
		doom->play[0].t.x -= step.y * doom->play[0].speed;
		doom->play[0].t.y -= doom->play[0].angle_x / 240;
	}
	if (doom->move.wsad[1])
	{
		doom->play[0].t.z -= step.x * doom->play[0].speed;
		doom->play[0].t.x += step.y * doom->play[0].speed;
		doom->play[0].t.y += doom->play[0].angle_x / 240;
	}
	if (doom->move.wsad[2])
	{
		doom->play[0].t.z -= step.y * doom->play[0].speed;
		doom->play[0].t.x -= step.x * doom->play[0].speed;
	}
	if (doom->move.wsad[3])
	{
		doom->play[0].t.z += step.y * doom->play[0].speed;
		doom->play[0].t.x += step.x * doom->play[0].speed;
	}
}

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
		calc_movement(doom);
	}
}

void	got_mouse_rot(t_editor *editor)
{
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

void	free_sec_toch(t_sec *sec)
{
	int	i;

	i = 0;
	while (i < sec->tex_y + 1)
	{
		ft_memdel((void **)&sec->toch[i]);
		i++;
	}
	ft_memdel((void **)&sec->toch);
}

void	rot_sec_by_z(t_doom *doom, int *points, t_dcoords coord, float rot_angle)
{
	doom->toch[points[1]].x = doom->toch[points[0]].x -\
						(coord.x * SDL_cos(rot_angle) - coord.y * SDL_sin(rot_angle));

	doom->toch[points[1]].y = doom->toch[points[0]].y -\
					(coord.x * SDL_sin(rot_angle) + coord.y * SDL_cos(rot_angle));


	doom->toch[points[2]].x = doom->toch[points[3]].x -\
					(coord.x * SDL_cos(rot_angle) - coord.y * SDL_sin(rot_angle));
	doom->toch[points[2]].y = doom->toch[points[3]].y -\
					(coord.x * SDL_sin(rot_angle) + coord.y * SDL_cos(rot_angle));
}

void	rot_sec_by_x(t_doom *doom, int *points, t_dcoords coord, float rot_angle)
{
	doom->toch[points[1]].y = doom->toch[points[0]].y -\
					(coord.y * SDL_cos(rot_angle) - coord.z * SDL_sin(rot_angle));
	doom->toch[points[1]].z = doom->toch[points[0]].z -\
					(coord.y * SDL_sin(rot_angle) + coord.z * SDL_cos(rot_angle));
	doom->toch[points[2]].y = doom->toch[points[3]].y -\
					(coord.y * SDL_cos(rot_angle) - coord.z * SDL_sin(rot_angle));
	doom->toch[points[2]].z = doom->toch[points[3]].z -\
					(coord.y * SDL_sin(rot_angle) + coord.z * SDL_cos(rot_angle));
}

void	rot_sector_by_wheel(t_editor *editor, SDL_Event event)
{
	int			aim;
	t_dcoords	coord;
	float		rot_angle;
	int			points[4];

	aim = editor->doom->aim_sp != -1 ? editor->doom->aim_sp : editor->doom->aim_sec;
	if (aim == -1)
		return ;
	if (editor->doom->aim_sp == -1)
	{
		points[0] = editor->doom->sec[aim].pts[0];
		points[1] = editor->doom->sec[aim].pts[1];
		points[2] = editor->doom->sec[aim].pts[2];
		points[3] = editor->doom->sec[aim].pts[3];
	}
	rot_angle = ((event.wheel.y > 0) ? 3 : -3) * PI / 180;
	coord.x = (float)editor->doom->sec[aim].v1.x;
	coord.y = (float)editor->doom->sec[aim].v1.y;
	coord.z = (float)editor->doom->sec[aim].v1.z;
	if (!editor->flags.t_f.rot_ax)
		rot_sec_by_x(editor->doom, points, coord, rot_angle);
	else
		rot_sec_by_z(editor->doom, points, coord, rot_angle);
	free_sec_toch(&editor->doom->sec[aim]);
	grid_sec(editor->doom, &editor->doom->sec[aim]);
}

void	god_rot_move(t_editor *editor, SDL_Event event)
{
	editor->doom->event = event;
	move_player(editor->doom);
	got_mouse_rot(editor);
	if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y)
			rot_sector_by_wheel(editor, event);
	}
}
