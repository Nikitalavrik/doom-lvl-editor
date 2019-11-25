/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:53:15 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/25 15:08:39 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	load_to_editor(t_editor *editor, char *filename)
{
	partly_free_editor(editor);
	free_doom(editor->doom);
	load_map(editor->doom, filename);
	convert_doom_to_editor(editor, editor->doom);
}

int		keyboard_events_down(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (event.key.keysym.sym == SDLK_s)
		editor->flags.t_f.select = editor->flags.t_f.select ? 0 : 1;
	else if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 1;
	else if (editor->flags.t_f.lctrl && event.key.keysym.sym == SDLK_z)
	{
		pop_line(&editor->lines);
		pop_point(&editor->point);
		editor->max_sectors--;
	}
	else if (event.key.keysym.sym == SDLK_SPACE && editor->point)
		close_room(editor);
	else if (event.key.keysym.sym == SDLK_c && editor->selected)
	{
		editor->flags.t_f.sprite = 1;
		editor->flags.t_f.select = 0;
	}
	else if (event.key.keysym.sym == SDLK_n)
	{
		if (!editor->flags.t_f.visual)
			d3_init(editor);
		else
			editor->flags.t_f.visual = 0;
		SDL_SetRelativeMouseMode(editor->flags.t_f.visual);
	}
	else if (event.key.keysym.sym == SDLK_l)
	{
		load_to_editor(editor, "saves/47504");
	}
	// else if (event.key.keysym.sym == SDLK_x)
	// 	d3_init(editor, 2);
	// else if (event.key.keysym.sym == SDLK_l)
	// 	d3_init(editor, 0);
	return (0);
}

int		keyboard_events_up(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 0;
	return (0);
}
