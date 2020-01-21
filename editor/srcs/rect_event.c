/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:07:18 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 18:07:19 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		get_nw_act_pole(t_editor *editor)
{
	if ((editor->new_win->mouse.x % editor->new_win->delim_x) > 20 &&\
		editor->new_win->mouse.x < C_WIDTH - 20 &&\
		((editor->new_win->mouse.y + editor->new_win->cam_y) %\
		editor->new_win->delim_y) > 20 && (editor->new_win->mouse.y +\
		editor->new_win->cam_y) < editor->new_win->mem_space)
		draw_rectangle(editor);
	get_pole_num(editor);
}
