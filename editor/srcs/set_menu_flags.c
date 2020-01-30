/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_menu_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:25:32 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 13:25:33 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int			set_lvl_flag(t_editor *editor, SDL_Event event)
{
	if (editor->param_sflag == 1 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.f_floor = 1;
		editor->flags.t_f.s_floor = 0;
		editor->flags.t_f.t_floor = 0;
		return (1);
	}
	else if (editor->param_sflag == 2 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.f_floor = 0;
		editor->flags.t_f.s_floor = 1;
		editor->flags.t_f.t_floor = 0;
		return (1);
	}
	else if (editor->param_sflag == 3 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.f_floor = 0;
		editor->flags.t_f.s_floor = 0;
		editor->flags.t_f.t_floor = 1;
		return (1);
	}
	return (0);
}

void		set_emenu_flag4(t_editor *editor, SDL_Event event)
{
	if (editor->param_flag == 10 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.clear_b = 1;
	}
	else if (editor->param_flag == 11 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.bselect = 1;
	}
	else if (!set_lvl_flag(editor, event))
		null_buttons(editor);
	else if (editor->param_flag == 0 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		set_to_zero_emenu_flags(editor);
	}
}

void		set_emenu_flag3(t_editor *editor, SDL_Event event)
{
	if (editor->param_flag == 7 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.ret_b = 1;
	}
	else if (editor->param_flag == 8 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.save_b = 1;
	}
	else if (editor->param_flag == 9 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.load_b = 1;
	}
	else
		set_emenu_flag4(editor, event);
}

void		set_emenu_flag2(t_editor *editor, SDL_Event event)
{
	if (editor->param_flag == 4 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.t_butt = 1;
	}
	else if (editor->param_flag == 5 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.d_butt = 1;
	}
	else if (editor->param_flag == 6 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		editor->flags.t_f.c_butt = 1;
	}
	else
		set_emenu_flag3(editor, event);
}

void		set_emenu_flag(t_editor *editor, SDL_Event event)
{
	if (editor->param_flag == 1 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.m_pole = 1;
	}
	else if (editor->param_flag == 2 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.f_butt = 1;
	}
	else if (editor->param_flag == 3 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		set_to_zero_emenu_flags(editor);
		editor->flags.t_f.s_butt = 1;
	}
	else
		set_emenu_flag2(editor, event);
}
