/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:56:47 by tbratsla          #+#    #+#             */
/*   Updated: 2020/01/21 17:56:48 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		free_nw_elements(t_editor *editor)
{
	int i;

	i = 0;
	ft_strdel(&editor->new_win->height_wall);
	ft_strdel(&editor->new_win->height_above);
	ft_strdel(&editor->new_win->transp);
	ft_strdel(&editor->new_win->f_height);
	ft_strdel(&editor->new_win->s_height);
	if (editor->new_win->param_flag == 3)
	{
		while (i < 7)
		{
			free(editor->new_win->editor_sprite[i].text[0].tex);
			free(editor->new_win->editor_sprite[i].text);
			i++;
		}
		free(editor->new_win->editor_sprite);
	}
}

void		close_choice_win(t_editor *editor)
{
	int		i;

	free_nw_elements(editor);
	i = 0;
	while (i < editor->new_win->mem_space)
	{
		free(editor->new_win->screen[i]);
		i++;
	}
	free(editor->new_win->screen);
	free(editor->new_win->events);
	SDL_FreeSurface(editor->new_win->sur);
	SDL_DestroyWindow(SDL_GetWindowFromID(editor->new_win->win_id));
	free(editor->new_win);
	editor->new_win = NULL;
}
