/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_new_win_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:30:46 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 17:30:48 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		save_wall_param(t_editor *editor)
{
	editor->new_win->param_par.line->height =\
	ft_atoi(editor->new_win->height_wall);
	editor->new_win->param_par.line->begin_height =\
	ft_atoi(editor->new_win->height_above);
	editor->new_win->param_par.line->num_of_textures =\
	(editor->new_win->active_num.tex_num + 1) % editor->doom->count_text;
	if (!editor->new_win->param_par.line->num_of_textures)
		editor->new_win->param_par.line->num_of_textures++;
}

void		save_room_param(t_editor *editor)
{
	editor->new_win->param_par.room->f_height =\
	ft_atoi(editor->new_win->f_height);
	editor->new_win->param_par.room->num_of_textures =\
	(editor->new_win->active_num.tex_num + 1) % editor->doom->count_text;
	if (!editor->new_win->param_par.room->num_of_textures)
		editor->new_win->param_par.room->num_of_textures++;
}

void		save_sprite_param(t_editor *editor)
{
	editor->new_win->param_par.sprite->num_of_textures =\
	(editor->new_win->active_num.tex_num + 1) % 7 + 9;
	editor->new_win->param_par.sprite->s_height =\
	ft_atoi(editor->new_win->s_height);
}

void		save_parametrs(t_editor *editor)
{
	if (editor->new_win->param_flag == 1)
		save_wall_param(editor);
	if (editor->new_win->param_flag == 2)
		save_room_param(editor);
	if (editor->new_win->param_flag == 3)
		save_sprite_param(editor);
}
