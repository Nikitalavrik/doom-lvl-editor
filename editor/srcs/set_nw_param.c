/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nw_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:52:29 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 17:52:30 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		set_wall_param(t_editor *editor, SDL_Event event)
{
	if ((event.type == SDL_TEXTINPUT ||\
		event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_1)
		write_to_pole(editor, &editor->new_win->height_wall, event);
	else if ((event.type == SDL_TEXTINPUT ||\
		event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_2)
		write_to_pole(editor, &editor->new_win->height_above, event);
}

void		set_room_param(t_editor *editor, SDL_Event event)
{
	if ((event.type == SDL_TEXTINPUT ||\
		event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_1)
		write_to_pole(editor, &editor->new_win->f_height, event);
}

void		set_sprite_param(t_editor *editor, SDL_Event event)
{
	if ((event.type == SDL_TEXTINPUT ||\
		event.key.type == SDL_KEYDOWN) && editor->flags.t_f.pole_1)
		write_to_pole(editor, &editor->new_win->s_height, event);
}

void		set_nw_param(t_editor *editor, SDL_Event event)
{
	if (editor->new_win->param_flag == 1)
		set_wall_param(editor, event);
	else if (editor->new_win->param_flag == 2)
		set_room_param(editor, event);
	else if (editor->new_win->param_flag == 3)
		set_sprite_param(editor, event);
}
