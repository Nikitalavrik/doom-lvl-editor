/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:53:15 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/30 18:28:20 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"



void	keyboard_for_visual(t_editor *editor, SDL_Event event)
{
	int		point[4];
	(void)event;
	(void)editor;
	if (event.key.keysym.sym == SDLK_UP)
	{
		if (editor->doom->aim_sec != -1)
		{
			point[0] = editor->doom->sec[editor->doom->aim_sec].pts[0];
			point[1] = editor->doom->sec[editor->doom->aim_sec].pts[1];
			point[2] = editor->doom->sec[editor->doom->aim_sec].pts[2];
			point[3] = editor->doom->sec[editor->doom->aim_sec].pts[3];
			editor->doom->toch[point[0]].y++;
			editor->doom->toch[point[1]].y++;
			editor->doom->toch[point[2]].y++;
			editor->doom->toch[point[3]].y++;
			grid_sec(editor->doom, &editor->doom->sec[editor->doom->aim_sec]);	
		}
		ft_printf("aim_sec = %i\n", editor->doom->aim_sec);
	}
}

int		check_rotation(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LEFT && editor->left_right < 0.7)
		editor->left_right += 0.1;
	else if (event.key.keysym.sym == SDLK_RIGHT && editor->left_right > -0.7)
		editor->left_right -= 0.1;
	else if (event.key.keysym.sym == SDLK_UP && editor->up_down < 1)
		editor->up_down += 0.1;
	else if (event.key.keysym.sym == SDLK_DOWN && editor->up_down > 0)
		editor->up_down -= 0.1;
	else
		return (0);
	return (1);
}

void	keyboard_for_editor(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_s)
		switch_to_select(editor);
	else if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 1;
	else if (editor->flags.t_f.lctrl && event.key.keysym.sym == SDLK_z)
		delete_prev(editor);
	else if (event.key.keysym.sym == SDLK_SPACE && editor->point)
		close_room(editor);
	else if (event.key.keysym.sym == SDLK_c && editor->selected)
		switch_to_sprite_put(editor);
	else if (event.key.keysym.sym == SDLK_l)
		switch_to_line_build(editor);
	else if (event.key.keysym.sym == SDLK_d)
		find_and_delete(editor);
	else if (event.key.keysym.sym == SDLK_f)
		switch_to_floor_build(editor);
	else if (check_rotation(editor, event))
		ft_printf("up_down = %f left_right = %f\n", editor->up_down, editor->left_right);
}

int		keyboard_events_down(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (event.key.keysym.sym == SDLK_n)
		switch_to_visual_3d(editor);
	if (editor->flags.t_f.visual)
		keyboard_for_visual(editor, event);
	else
		keyboard_for_editor(editor, event);
	return (0);
}

int		keyboard_events_up(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 0;
	return (0);
}
