/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:58:41 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/20 16:50:05 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	delete_line(t_editor *editor, t_eline *line)
{
	t_eline *next;
	t_eline *prev;

	next = line->next;
	prev = line->prev;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (line == editor->lines)
		editor->lines = next;
	ft_memdel((void **)&line);
}

void        push_line(t_eline **begin, t_epoint *point1, t_epoint *point2)
{
	t_eline *iterator;
	t_eline *new_point;

	new_point = ft_memalloc(sizeof(t_eline));
	new_point->points[0] = point1;
	new_point->points[1] = point2;
	new_point->points[2] = ft_memalloc(sizeof(t_epoint));
	new_point->points[3] = ft_memalloc(sizeof(t_epoint));
	new_point->points[2]->x = point1->x;
	new_point->points[2]->y = point1->y;
	new_point->points[3]->x = point2->x;
	new_point->points[3]->y = point2->y;
	if (*begin)
	{
		iterator = *begin;
		new_point->next = iterator;
		iterator->prev = new_point;
		*begin = new_point;
	}
	else
		*begin = new_point;
}

void		pop_line(t_eline **begin)
{
	t_eline *next_begin;
	t_eline *iterator;

	iterator = *begin;
	if (iterator && iterator->next)
	{
		next_begin = iterator->next;
		next_begin->prev = NULL;
		ft_memdel((void **)&iterator);
		*begin = next_begin;
	}
	else if (iterator)
	{
		ft_memdel((void **)&iterator);
		*begin = NULL;
	}
}

t_eline	*find_line_by_id(t_editor *editor, int id)
{
	t_eline	*iter;

	iter = editor->lines;
	while (iter)
	{
		if (iter->id == id)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void	add_line(t_editor *editor)
{
	t_coords 	mouse_position;
	t_coords	coord;
	t_coords	*finded;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	coord = get_coords(editor, mouse_position);
	if (coord.x != INT16_MAX)
	{
		finded = &editor->coords[coord.y][coord.x];
		if (mouse_position.x <= finded->x + (int)(finded->r * editor->zoom) &&\
			mouse_position.x >= finded->x - (int)(finded->r * editor->zoom) &&\
			mouse_position.y <= finded->y + (int)(finded->r * editor->zoom) &&\
			mouse_position.y >= finded->y - (int)(finded->r * editor->zoom))
			{
				push_point(&editor->point, finded);
				editor->point->x = coord.x;
				editor->point->y = coord.y;
				editor->point_cnt++;
				if (editor->point_cnt >= 2 && editor->point && editor->point->next)
				{
					editor->point_cnt = 1;
					push_line(&editor->lines, editor->point, editor->point->next);
					editor->lines->color = WALL_COLOR;
					editor->lines->height = 20;
					editor->lines->floor = editor->floor;
					editor->lines->num_of_textures = 14;
					editor->max_sectors++;
				}
			}
	}
}
