/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:56:57 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 18:11:44 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	null_editing_flags(t_flags *flags)
{
	flags->t_f.line = 0;
	flags->t_f.select = 0;
	flags->t_f.floor = 0;
	flags->t_f.sprite = 0;
	flags->t_f.m_pole = 0;
	flags->t_f.f_butt = 0;
	flags->t_f.s_butt = 0;
	flags->t_f.t_butt = 0;
	flags->t_f.d_butt = 0;
}

void	set_to_zero_emenu_flags(t_editor *editor)
{
	editor->flags.t_f.m_pole = 0;
	editor->flags.t_f.f_butt = 0;
	editor->flags.t_f.s_butt = 0;
	editor->flags.t_f.t_butt = 0;
	editor->flags.t_f.d_butt = 0;
	editor->flags.t_f.ret_b = 0;
	editor->flags.t_f.save_b = 0;
	editor->flags.t_f.c_butt = 0;
	editor->flags.t_f.load_b = 0;
	editor->flags.t_f.clear = 0;
}

void	null_buttons(t_editor *editor)
{
	editor->flags.t_f.bselect = 0;
	editor->flags.t_f.c_butt = 0;
	editor->flags.t_f.ret_b = 0;
	editor->flags.t_f.save_b = 0;
	editor->flags.t_f.load_b = 0;
	editor->flags.t_f.clear = 0;
}
