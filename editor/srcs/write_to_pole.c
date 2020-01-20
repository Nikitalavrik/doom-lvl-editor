/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_pole.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:46:03 by tbratsla          #+#    #+#             */
/*   Updated: 2019/11/30 12:46:04 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	set_active_pole(t_editor *editor)
{
	Uint32 color;

	draw_white_space(editor->new_win->ws_coord1, editor->new_win->sur,\
	color = editor->flags.t_f.pole_1 == 1 ? ACT_BACK : BACKGROUND);
	if (editor->new_win->param_flag == 1)
	{
		draw_white_space(editor->new_win->ws_coord2, editor->new_win->sur,\
		color = editor->flags.t_f.pole_2 == 1 ? ACT_BACK : BACKGROUND);
	}
	rewrite_text_to_pole(editor);
}

void	get_pole_num(t_editor *editor)
{
	if (editor->new_win->mouse.x > editor->new_win->ws_coord1.x &&\
		editor->new_win->mouse.x < editor->new_win->ws_coord1.x1 &&\
		editor->new_win->mouse.y > editor->new_win->ws_coord1.y &&\
		editor->new_win->mouse.y < editor->new_win->ws_coord1.y1)
	{
		editor->flags.t_f.pole_1 = 1;
		editor->flags.t_f.pole_2 = 0;
	}
	else if (editor->new_win->mouse.x > editor->new_win->ws_coord2.x &&\
		editor->new_win->mouse.x < editor->new_win->ws_coord2.x1 &&\
		editor->new_win->mouse.y > editor->new_win->ws_coord2.y &&\
		editor->new_win->mouse.y < editor->new_win->ws_coord2.y1)
	{
		editor->flags.t_f.pole_1 = 0;
		editor->flags.t_f.pole_2 = 1;
	}
	else
	{
		editor->flags.t_f.pole_1 = 0;
		editor->flags.t_f.pole_2 = 0;
	}
	set_active_pole(editor);
}

t_coord	get_coord_from_flag(t_editor *editor)
{
	if (editor->flags.t_f.pole_1 == 1)
		return (editor->new_win->ws_coord1);
	if (editor->flags.t_f.pole_2 == 1)
		return (editor->new_win->ws_coord2);
	return (editor->new_win->ws_coord1);
}

void	rewrite_text_to_pole(t_editor *editor)
{
	if (editor->new_win->param_flag == 1)
	{
		add_text_to_space(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, editor->new_win->height_wall);
		add_text_to_space(editor, editor->new_win->ws_coord2,\
		editor->new_win->win, editor->new_win->height_above);
	}
	if (editor->new_win->param_flag == 2)
	{
		add_text_to_space(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, editor->new_win->f_height);
	}
	if (editor->new_win->param_flag == 3)
	{
		add_text_to_space(editor, editor->new_win->ws_coord1,\
		editor->new_win->win, editor->new_win->s_height);
	}
}

void	write_to_pole(t_editor *editor, char **text, SDL_Event event)
{
	t_coord		coord;
	char		*tmp;

	coord = get_coord_from_flag(editor);
	if (event.key.type == SDL_KEYDOWN &&\
		event.key.keysym.sym == SDLK_BACKSPACE && ft_strlen(*text) > 0)
	{
		tmp = *text;
		*text = ft_strsub(tmp, 0, ft_strlen(*text) - 1);
		free(tmp);
	}
	else if (event.type == SDL_TEXTINPUT &&\
		ft_strlen(*text) < 3 &&\
		event.text.text[0] >= '0' && event.text.text[0] <= '9')
	{
		tmp = *text;
		*text = ft_strjoin(tmp, event.text.text);
		free(tmp);
	}
	draw_white_space(coord, editor->new_win->sur, ACT_BACK);
	add_text_to_space(editor, coord, editor->new_win->win, *text);
}
