/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_switch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:50 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:31:31 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	switch_to_select(t_editor *editor)
{
	editor->flags.t_f.select = editor->flags.t_f.select ? 0 : 1;
	editor->flags.t_f.floor = 0;
	if (editor->flags.t_f.select)
		delete_stick_point(editor);
}

void	switch_to_floor_build(t_editor *editor)
{
	editor->flags.t_f.floor = editor->flags.t_f.floor ? 0 : 1;
	editor->flags.t_f.select = 0;
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
