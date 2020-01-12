/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:11:09 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/12 17:30:45 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		delete_sprite(t_editor *editor, t_esprite *sprite)
{
	t_esprite *next;
	t_esprite *prev;
	if (editor->selected)
	{
		next = sprite->next;
		prev = sprite->prev;
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		if (sprite == editor->selected->sprites)
			editor->selected->sprites = next;
		ft_memdel((void **)&sprite);
	}
}

void		push_sprite(t_esprite **begin, t_coords *coord)
{
	t_esprite *iterator;
	t_esprite *new_point;

	new_point = ft_memalloc(sizeof(t_esprite));
	new_point->coord = coord;
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

void		pop_sprite(t_esprite **begin)
{
	t_esprite *next_begin;
	t_esprite *iterator;

	iterator = *begin;
	if (iterator && iterator->next)
	{
		next_begin = iterator->next;
		next_begin->prev = NULL;
		iterator->coord = NULL;
		ft_memdel((void **)&iterator);
		*begin = next_begin;
	}
	else if (iterator)
	{
		ft_memdel((void **)&iterator);
		*begin = NULL;
	}
}

/*
** check nearest sprite
*/

int		check_sprites(t_esprite *sprites, t_coords mouse, double zoom)
{
	int			dist;
	t_esprite	*iter;

	iter = sprites;
	while (iter)
	{
		dist = sqrt(pow(mouse.x - iter->coord->x - iter->dist.x, 2) +\
		pow(mouse.y - iter->coord->y - iter->dist.y, 2));
		if (dist <= (SPRITE_SIZE + 2) * zoom)
			return (0);
		iter = iter->next;
	}
	return (1);
}

void	add_sprite(t_editor *editor)
{
	t_coords	max;
	t_coords	min;
	t_coords	coord;
	int			size;
	t_coords	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	coord = get_coords(editor, mouse);
	min = editor->coords[editor->selected->min_xy.y][editor->selected->min_xy.x];
	max = editor->coords[editor->selected->max_xy.y][editor->selected->max_xy.x];
	size = SPRITE_SIZE * editor->zoom / 2;
	if (mouse.x - size >= min.x && mouse.x + size <= max.x\
		&& mouse.y - size >= min.y && mouse.y + size <= max.y)
	{
		if (coord.x != INT16_MAX)
		{
			if (check_sprites(editor->selected->sprites, mouse, editor->zoom))
			{
				push_sprite(&editor->selected->sprites, &editor->coords[coord.y][coord.x]);
				editor->selected->sprites->origin.x = (mouse.x -\
				editor->coords[coord.y][coord.x].x) / editor->zoom;
				editor->selected->sprites->origin.y = (mouse.y -\
				editor->coords[coord.y][coord.x].y) / editor->zoom;
				editor->selected->sprites->size = SPRITE_SIZE * editor->zoom;
				editor->selected->sprites->alpha = 140;
				editor->selected->sprites->num_of_textures = 5;
				editor->selected->sprites->x = coord.x;
				editor->selected->sprites->y = coord.y;
				editor->selected->max_sprites++;
			}
		}
	}
}
