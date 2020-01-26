/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:38:00 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/26 14:26:06 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		check_position(t_coords mouse_position, t_coord coord)
{
	if (mouse_position.x > coord.x &&
		mouse_position.x < coord.x1 &&
		mouse_position.y > coord.y &&
		mouse_position.y < coord.y1)
		return (1);
	return (0);
}

int		check_emenu_scursor(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.third_floor))
	{
		editor->param_sflag = 3;
		return (1);
	}
	else if (check_position(mouse_position,\
		editor->menu.second_floor))
	{
		editor->param_sflag = 2;
		return (1);
	}
	else if (check_position(mouse_position,\
		editor->menu.first_floor))
	{
		editor->param_sflag = 1;
		return (1);
	}
	else
		editor->param_sflag = 0;
	return (0);
}

void	write_to_emenu_pole(SDL_Event event, char **text)
{
	char *tmp;

	if (event.key.type == SDL_KEYDOWN &&\
		event.key.keysym.sym == SDLK_BACKSPACE && ft_strlen(*text) > 0)
	{
		tmp = *text;
		*text = ft_strsub(tmp, 0, ft_strlen(*text) - 1);
		free(tmp);
	}
	else if (event.type == SDL_TEXTINPUT &&\
		ft_strlen(*text) < 20)
	{
		tmp = *text;
		*text = ft_strjoin(tmp, event.text.text);
		free(tmp);
	}
}

int		editor_menu_events(t_editor *editor, \
	t_coords mouse_position, SDL_Event event)
{
	check_emenu_cursor(editor, mouse_position);
	set_emenu_flag(editor, event);
	if (editor->flags.t_f.m_pole == 1)
		write_to_emenu_pole(event, &editor->filename);
	return (editor->flags.t_f.ret_b);
}
