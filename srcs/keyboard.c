/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:53:15 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 18:14:30 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		keyboard_events_down(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (event.key.keysym.sym == SDLK_s)
		switch_to_select(editor);
	else if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 1;
	else if (editor->flags.t_f.lctrl && event.key.keysym.sym == SDLK_z)
		delete_prev(editor);
	else if (event.key.keysym.sym == SDLK_SPACE && editor->point)
		close_room(editor);
	else if (event.key.keysym.sym == SDLK_c && editor->selected)
		switch_to_sprite_put(editor);
	else if (event.key.keysym.sym == SDLK_n)
		switch_to_visual_3d(editor);
	else if (event.key.keysym.sym == SDLK_l)
		switch_to_line_build(editor);
	else if (event.key.keysym.sym == SDLK_d)
		find_and_delete(editor);
	else if (event.key.keysym.sym == SDLK_f)
		switch_to_floor_build(editor);
	return (0);
}

int		keyboard_events_up(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 0;
	return (0);
}
