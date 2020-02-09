/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ques_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:57:13 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/30 17:57:14 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	close_ques_win(t_editor *editor)
{
	SDL_FreeSurface(editor->ques_surf);
	SDL_DestroyWindow(editor->ques_win);
	editor->ques_win = NULL;
}

void	set_ques_flag(t_editor *editor, t_coords mouse_position)
{
	if (check_position(mouse_position, editor->menu.yes_button))
		editor->ques_flag = 1;
	else if (check_position(mouse_position, editor->menu.no_button))
		editor->ques_flag = 2;
	else
		editor->ques_flag = 0;
}

void	ques_event2(t_editor *editor, SDL_Event event)
{
	if (editor->ques_flag == 1 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		editor->flags.t_f.rewrite = 1;
		SDL_BlitScaled(editor->button[10], NULL,\
			editor->ques_surf, &editor->menu.rect1);
		close_ques_win(editor);
		return ;
	}
	else if (editor->ques_flag == 2 &&
		event.button.button == SDL_BUTTON_LEFT &&
		event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_BlitScaled(editor->button[10], NULL,\
			editor->ques_surf, &editor->menu.rect2);
		editor->flags.t_f.rewrite = 0;
		close_ques_win(editor);
		return ;
	}
}

void	ques_event(t_editor *editor, SDL_Event event, t_coords mouse_position)
{
	set_ques_flag(editor, mouse_position);
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		close_ques_win(editor);
		return ;
	}
	if (editor->ques_flag == 1)
		SDL_BlitScaled(editor->button[9], NULL,\
			editor->ques_surf, &editor->menu.rect1);
	else if (editor->ques_flag == 2)
		SDL_BlitScaled(editor->button[9], NULL,\
			editor->ques_surf, &editor->menu.rect2);
	else
	{
		SDL_BlitScaled(editor->button[8], NULL,\
			editor->ques_surf, &editor->menu.rect2);
		SDL_BlitScaled(editor->button[8], NULL,\
			editor->ques_surf, &editor->menu.rect1);
	}
	ques_button_names(editor);
	ques_event2(editor, event);
}
