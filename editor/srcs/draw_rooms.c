/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:18:43 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/20 16:52:16 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	draw_stick_room(t_editor *editor)
{
	t_coords 	iter;
	t_coords 	max;
	t_coords	min;

	if (editor->stick_room)
	{
		min.x = editor->stick_room->point->coord->x < editor->stick_room->point->next->coord->x ?\
		editor->stick_room->point->coord->x : editor->stick_room->point->next->coord->x;
		min.y = editor->stick_room->point->coord->y < editor->stick_room->point->next->coord->y ?\
		editor->stick_room->point->coord->y : editor->stick_room->point->next->coord->y;
		iter.x = min.x;
		max.x = editor->stick_room->point->coord->x > editor->stick_room->point->next->coord->x ?\
		editor->stick_room->point->coord->x : editor->stick_room->point->next->coord->x;
		max.y = editor->stick_room->point->coord->y > editor->stick_room->point->next->coord->y ?\
		editor->stick_room->point->coord->y : editor->stick_room->point->next->coord->y;
		while (iter.x < max.x)
		{
			iter.y = min.y;
			while (iter.y < max.y)
			{
				put_epixel(editor, iter.x, iter.y,\
				alpha_grad(TEXTURE_COLOR, 0, editor->stick_room->alpha));
				iter.y++;
			}
			iter.x++;
		}
	}
}

void		draw_square(t_editor *editor, t_esprite *sprite)
{
	t_coords	max;
	t_coords	iter;

	sprite->size = SPRITE_SIZE * editor->zoom;
	sprite->dist.x = (sprite->origin.x + sprite->move.x) * editor->zoom;
	sprite->dist.y = (sprite->origin.y + sprite->move.y) * editor->zoom;
	max.x = sprite->coord->x + sprite->dist.x + sprite->size / 2;
	max.y = sprite->coord->y + sprite->dist.y + sprite->size / 2;
	iter.y = sprite->coord->y + sprite->dist.y - sprite->size / 2;
	while (iter.y < max.y)
	{
		iter.x = sprite->coord->x + sprite->dist.x - sprite->size / 2;
		while (iter.x < max.x)
		{
			put_epixel(editor, iter.x, iter.y, alpha_grad(SPRITE_COLOR, 0, sprite->alpha));
			iter.x++;
		}
		iter.y++;
	}
}

void		draw_sprite(t_editor *editor, t_esprite *sprites)
{
	t_esprite	*iter;

	iter = sprites;
	while (iter)
	{
		draw_square(editor, iter);
		iter = iter->next;
	}
}

void		draw_texture_room(t_editor *editor, t_room *iterate_room)
{
	t_coords 	iter;
	t_coords 	max;

	iter.x = editor->coords[iterate_room->min_xy.y][iterate_room->min_xy.x].x + 1;
	max.x = editor->coords[iterate_room->max_xy.y][iterate_room->max_xy.x].x;
	max.y = editor->coords[iterate_room->max_xy.y][iterate_room->max_xy.x].y;
	while (iter.x < max.x)
	{
		iter.y = editor->coords[iterate_room->min_xy.y][iterate_room->min_xy.x].y;
		while (iter.y < max.y)
		{
			put_epixel(editor, iter.x, iter.y,\
			alpha_grad(TEXTURE_COLOR, 0, iterate_room->alpha));
			iter.y++;
		}
		iter.x++;
	}	
}

void        draw_rooms(t_editor *editor)
{
	t_room	*iterate_room;

	iterate_room = editor->rooms;
	while (iterate_room)
	{
		if (iterate_room->floor == editor->floor)
		{
			draw_texture_room(editor, iterate_room);
			draw_sprite(editor, iterate_room->sprites);			
		}
		iterate_room = iterate_room->next;
	}
}
