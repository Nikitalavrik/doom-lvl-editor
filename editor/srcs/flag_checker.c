/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:41:51 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/30 15:58:34 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	check_emenu_pole2(t_editor *editor)
{
	if (editor->flags.t_f.save_b == 1)
	{
		if (!editor->filename[0])
			editor->flags.t_f.error = 1;
		else
		{
			if (check_file_in_dir(editor->filename))
			{
				d3_init(editor);
				editor_autosave(editor);
			}
			editor->flags.t_f.visual = 0;
		}
	}
	if (editor->flags.t_f.load_b == 1)
	{
		if (!check_file_in_dir(editor->filename))
			load_to_editor(editor, editor->filename);
	}
	if (editor->flags.t_f.bselect == 1)
		editor->flags.t_f.select = 1;
	if (editor->filename[0])
		editor->flags.t_f.error = 0;
	if (editor->flags.t_f.error == 1)
		draw_error_mess(editor);
	null_buttons(editor);
}

void	check_emenu_pole(t_editor *editor)
{
	if (editor->flags.t_f.f_butt == 1)
		switch_to_line_build(editor);
	if (editor->flags.t_f.s_butt == 1 && !editor->flags.t_f.floor)
		switch_to_floor_build(editor);
	if (editor->flags.t_f.t_butt == 1 && editor->selected)
		switch_to_sprite_put(editor);
	if (editor->flags.t_f.d_butt == 1 && editor->flags.t_f.select == 1)
		find_and_delete(editor);
	if (editor->flags.t_f.c_butt == 1 && editor->point)
		close_room(editor);
	if (editor->flags.t_f.f_floor == 1)
		editor->floor = 1;
	else if (editor->flags.t_f.s_floor == 1)
		editor->floor = 2;
	else if (editor->flags.t_f.t_floor == 1)
		editor->floor = 3;
	check_emenu_pole2(editor);
}
