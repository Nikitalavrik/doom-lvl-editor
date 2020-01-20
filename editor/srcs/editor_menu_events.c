/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:38:00 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/12 16:38:01 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		set_emenu_sflag(t_editor *editor, SDL_Event event)
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
	else if (editor->param_sflag  == 3 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.f_floor = 0;
		editor->flags.t_f.s_floor = 0;
		editor->flags.t_f.t_floor = 1;
		return (1);
	}
	return (0);
}

int			check_emenu_scursor(t_editor *editor, t_coords mouse_position)
{
	if (mouse_position.x >= editor->menu.third_floor.x &&
		mouse_position.x <= editor->menu.third_floor.x1 &&
		mouse_position.y >= editor->menu.third_floor.y &&
		mouse_position.y <= editor->menu.third_floor.y1)
	{

		editor->param_sflag = 3;
		return (1);
	}
	if (mouse_position.x >= editor->menu.second_floor.x &&
		mouse_position.x <= editor->menu.second_floor.x1 &&
		mouse_position.y >= editor->menu.second_floor.y &&
		mouse_position.y <= editor->menu.second_floor.y1)
	{

		editor->param_sflag = 2;
		return (1);
	}
	if (mouse_position.x >= editor->menu.first_floor.x &&
		mouse_position.x <= editor->menu.first_floor.x1 &&
		mouse_position.y >= editor->menu.first_floor.y &&
		mouse_position.y <= editor->menu.first_floor.y1)
	{

		editor->param_sflag = 1;
		return (1);
	}
	return (0);
}

void		set_emenu_flag(t_editor *editor, SDL_Event event)
{
	if (editor->param_flag == 1 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.m_pole = 1;
		editor->flags.t_f.f_butt = 0;
		editor->flags.t_f.s_butt = 0;
		editor->flags.t_f.t_butt = 0;
		editor->flags.t_f.d_butt = 0;
	}
	else if (editor->param_flag == 2 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.m_pole = 0;
		editor->flags.t_f.f_butt = 1;
		editor->flags.t_f.s_butt = 0;
		editor->flags.t_f.t_butt = 0;
		editor->flags.t_f.d_butt = 0;
	}
	else if (editor->param_flag  == 3 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.m_pole = 0;
		editor->flags.t_f.f_butt = 0;
		editor->flags.t_f.s_butt = 1;
		editor->flags.t_f.t_butt = 0;
		editor->flags.t_f.d_butt = 0;
	}
	else if (editor->param_flag == 4 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.m_pole = 0;
		editor->flags.t_f.f_butt = 0;
		editor->flags.t_f.s_butt = 0;
		editor->flags.t_f.t_butt = 1;
		editor->flags.t_f.d_butt = 0;
	}
	else if (editor->param_flag == 5 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.m_pole = 0;
		editor->flags.t_f.f_butt = 0;
		editor->flags.t_f.s_butt = 0;
		editor->flags.t_f.t_butt = 0;
		editor->flags.t_f.d_butt = 1;
	}
	else if (editor->param_flag == 0 &&\
		event.button.clicks == 1 && event.button.button == SDL_BUTTON_LEFT)
	{
		editor->flags.t_f.m_pole = 0;
		editor->flags.t_f.f_butt = 0;
		editor->flags.t_f.s_butt = 0;
		editor->flags.t_f.t_butt = 0;
		editor->flags.t_f.d_butt = 0;
	}
	if (editor->param_flag == 6 &&
		event.button.button == SDL_BUTTON_LEFT && 
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		editor->flags.t_f.m_pole = 0;
		editor->flags.t_f.f_butt = 0;
		editor->flags.t_f.s_butt = 0;
		editor->flags.t_f.t_butt = 0;
		editor->flags.t_f.d_butt = 0;
		editor->flags.t_f.c_butt = 1;
	}
	else if (!set_emenu_sflag(editor, event))
		editor->flags.t_f.c_butt = 0;
}

void		write_to_emenu_pole(SDL_Event event, char **text)
{
	char *tmp;

	if (event.key.type == SDL_KEYDOWN &&\
		event.key.keysym.sym == SDLK_BACKSPACE && ft_strlen(*text) > 0)
	{
		tmp = *text;
		*text = ft_strsub(tmp, 0, ft_strlen(*text) - 1);
		free(tmp);
	}
	else if (event.type == SDL_TEXTINPUT &&\
		ft_strlen(*text) < 20)
	{
		tmp = *text;
		*text = ft_strjoin(tmp, event.text.text);
		free(tmp);
	}
}

void		check_emenu_cursor(t_editor *editor, t_coords mouse_position)
{
	if (mouse_position.x >= editor->menu.coord.x &&
		mouse_position.x <= editor->menu.coord.x1 &&
		mouse_position.y >= editor->menu.coord.y &&
		mouse_position.y <= editor->menu.coord.y1)
		editor->param_flag = 1;
	else if (mouse_position.x >= editor->menu.f_cb_coord.x &&
		mouse_position.x <= editor->menu.f_cb_coord.x1 &&
		mouse_position.y >= editor->menu.f_cb_coord.y &&
		mouse_position.y <= editor->menu.f_cb_coord.y1)
	{
		editor->param_flag = 2;
	}
	else if (mouse_position.x >= editor->menu.s_cb_coord.x &&
		mouse_position.x <= editor->menu.s_cb_coord.x1 &&
		mouse_position.y >= editor->menu.s_cb_coord.y &&
		mouse_position.y <= editor->menu.s_cb_coord.y1)
	{
		editor->param_flag = 3;
	}
	else if (mouse_position.x >= editor->menu.t_cb_coord.x &&
		mouse_position.x <= editor->menu.t_cb_coord.x1 &&
		mouse_position.y >= editor->menu.t_cb_coord.y &&
		mouse_position.y <= editor->menu.t_cb_coord.y1)
	{
		editor->param_flag = 4;
	}
	else if (mouse_position.x >= editor->menu.del_cb_coord.x &&
		mouse_position.x <= editor->menu.del_cb_coord.x1 &&
		mouse_position.y >= editor->menu.del_cb_coord.y &&
		mouse_position.y <= editor->menu.del_cb_coord.y1)
	{
		editor->param_flag = 5;
	}
	else if (mouse_position.x >= editor->menu.clo_cb_coord.x &&
		mouse_position.x <= editor->menu.clo_cb_coord.x1 &&
		mouse_position.y >= editor->menu.clo_cb_coord.y &&
		mouse_position.y <= editor->menu.clo_cb_coord.y1)
	{
		editor->param_flag = 6;
	}
	else if (!check_emenu_scursor(editor, mouse_position))
		editor->param_flag = 0;
}


void	editor_menu_events(t_editor *editor, t_coords mouse_position, SDL_Event event)
{
	check_emenu_cursor(editor, mouse_position);
	set_emenu_flag(editor, event);
	if (editor->flags.t_f.m_pole == 1)
		write_to_emenu_pole(event, &editor->filename);

}
