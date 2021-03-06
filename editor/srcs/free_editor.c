/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:40:42 by nlavrine          #+#    #+#             */
/*   Updated: 2020/02/09 14:54:39 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		free_points(t_epoint **point)
{
	while (*point)
		pop_point(point);
}

void		free_lines(t_eline **line)
{
	t_eline	*iter;

	iter = *line;
	while (iter)
	{
		*line = (*line)->next;
		ft_memdel((void **)&iter);
		iter = *line;
	}
	line = NULL;
}

void		free_sprites(t_esprite **sprites)
{
	t_esprite *iter;

	iter = *sprites;
	while (iter)
	{
		*sprites = (*sprites)->next;
		ft_memdel((void **)&iter);
		iter = *sprites;
	}
	sprites = NULL;
}

void		free_rooms(t_room **room)
{
	t_room	*iter;

	iter = *room;
	while (iter)
	{
		*room = (*room)->next;
		free_points(&iter->point);
		free_sprites(&iter->sprites);
		ft_memdel((void **)&iter);
		iter = *room;
	}
	room = NULL;
}

void		partly_free_editor(t_editor *editor)
{
	free_rooms(&editor->rooms);
	free_points(&editor->point);
	free_lines(&editor->lines);
	editor->selected = NULL;
}
