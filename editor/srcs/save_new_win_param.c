/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_new_win_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:30:46 by tbratsla          #+#    #+#             */
/*   Updated: 2020/03/01 15:24:54 by nlavrine         ###   ########.fr       */
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
	editor->new_win->param_par.room->height =\
	ft_atoi(editor->new_win->f_height);
	editor->new_win->param_par.room->num_of_textures =\
	(editor->new_win->active_num.tex_num + 1) % editor->doom->count_text;
	if (!editor->new_win->param_par.room->num_of_textures)
		editor->new_win->param_par.room->num_of_textures++;
}

void		save_sprite_param(t_editor *editor)
{
	int	new_num;
	int	prev_num;

	prev_num = editor->new_win->param_par.sprite->num_of_textures;
	new_num = (editor->new_win->active_num.tex_num + 1) % 7 + 9;
	if (prev_num >= 9 && prev_num <= 11
					&& !(new_num >= 9 && new_num <= 11))
	{
		editor->new_win->param_par.sprite->room->max_mobs--;
		editor->new_win->param_par.sprite->room->max_sprites++;
	}
	else if (!(prev_num >= 9 && prev_num <= 11)
					&& new_num >= 9 && new_num <= 11)
	{
		editor->new_win->param_par.sprite->room->max_mobs++;
		editor->new_win->param_par.sprite->room->max_sprites--;
	}
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
