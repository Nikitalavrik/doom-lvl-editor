/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_switch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:50 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 18:14:04 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	switch_to_sprite_put(t_editor *editor)
{
	null_editing_flags(&editor->flags);
	editor->flags.t_f.sprite = 1;
	editor->flags.t_f.t_butt = 1;
}

void	switch_to_select(t_editor *editor)
{
	if (editor->flags.t_f.line || editor->flags.t_f.floor)
		delete_stick_point(editor);
	null_editing_flags(&editor->flags);
	editor->flags.t_f.select = 1;

}

void	switch_to_line_build(t_editor *editor)
{
	null_editing_flags(&editor->flags);
	editor->flags.t_f.line = 1;
	editor->flags.t_f.f_butt = 1;
}

void	switch_to_floor_build(t_editor *editor)
{
	null_editing_flags(&editor->flags);
	editor->flags.t_f.floor = 1;
	editor->flags.t_f.s_butt = 1;
	delete_stick_point(editor);
}

void	switch_to_visual_3d(t_editor *editor)
{
	if (!editor->flags.t_f.visual)
		d3_init(editor);
	else
		editor->flags.t_f.visual = 0;
	SDL_SetRelativeMouseMode(editor->flags.t_f.visual);
}
