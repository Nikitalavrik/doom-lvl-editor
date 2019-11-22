/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:55:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/22 13:54:23 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		get_epixel(t_editor *editor, int x, int y)
{
	if (x >= 0 && x < E_WIDTH - MENU_WIDTH && y >= 0 && y < E_HEIGHT)
		return (((int *)editor->surf->pixels)[(y * editor->surf->w) + x]);
	return (-1);
}

void	put_epixel(t_editor *editor, int x, int y, int color)
{
	if (x >= 0 && x < E_WIDTH - MENU_WIDTH && y >= 0 && y < E_HEIGHT)
		((int *)editor->surf->pixels)[(y * editor->surf->w) + x] = color;
}

t_coords	calc_delta(t_coords coord0, t_coords coord1,
											t_coords *delta, t_coords *iter)
{
	t_coords coord;

	coord.x = coord0.x;
	coord.y = coord0.y;
	delta->x = abs(coord1.x - coord0.x);
	delta->y = -abs(coord1.y - coord0.y);
	iter->x = coord0.x < coord1.x ? 1 : -1;
	iter->y = coord0.y < coord1.y ? 1 : -1;
	return (coord);
}

void		draw_eline(t_editor *editor, t_coords coord0,
										t_coords coord1, int color)
{
	t_coords	coord;
	t_coords	delta;
	t_coords	iter;
	t_coords	error;

	coord = calc_delta(coord0, coord1, &delta, &iter);
	error.x = delta.x + delta.y;
	while (1 && !((coord0.x < 0 && coord1.x < 0) ||\
	(coord0.y < 0 && coord1.y < 0)))
	{
		put_epixel(editor, coord.x, coord.y, color);
		if (((coord.x == coord1.x)\
					&& (coord.y == coord1.y)) || (coord.x < 0 && coord.y < 0))
			break ;
		error.y = error.x + 1;
		if (error.y >= delta.y && coord.x != coord1.x)
		{
			error.x += delta.y;
			coord.x += iter.x;
		}
		if (error.y <= delta.x && coord.y != coord1.y)
		{
			error.x += delta.x;
			coord.y += iter.y;
		}
	}
}

void drawCircle(t_editor *editor, t_coords coord0, t_coords coord1, int color) 
{ 
    put_epixel(editor, coord0.x + coord1.x, coord0.y + coord1.y, color); 
    put_epixel(editor, coord0.x - coord1.x, coord0.y + coord1.y, color); 
    put_epixel(editor, coord0.x + coord1.x, coord0.y - coord1.y, color); 
    put_epixel(editor, coord0.x - coord1.x, coord0.y - coord1.y, color); 
    put_epixel(editor, coord0.x + coord1.y, coord0.y + coord1.x, color); 
    put_epixel(editor, coord0.x - coord1.y, coord0.y + coord1.x, color); 
    put_epixel(editor, coord0.x + coord1.y, coord0.y - coord1.x, color); 
    put_epixel(editor, coord0.x - coord1.y, coord0.y - coord1.x, color); 
} 

void circle_Bres(t_editor *editor, t_coords coord0, int color) 
{
	int 		d;
	int			r;
	t_coords	coord1;

	r = (int)(coord0.r * editor->zoom);
	coord1.x = 0;
	coord1.y = r;
	d = 3 - 2 * r;
    drawCircle(editor, coord0, coord1 , color); 
    while (coord1.y >= coord1.x) 
    {
        coord1.x++; 
        if (d > 0) 
        { 
            coord1.y--;  
            d = d + 4 * (coord1.x - coord1.y) + 10; 
        } 
        else
            d = d + 4 * coord1.x + 6; 
        drawCircle(editor, coord0, coord1 , color);  
    } 
} 

void		draw_cells(t_editor *editor)
{
	t_coords	step;

	step.y = 0;
	coords_rerange(editor);
	while (step.y < editor->size.y)
	{
		step.x = 0;
		while (step.x < editor->size.x)
		{
			circle_Bres(editor, editor->coords[step.y][step.x], STANDART_COLOR);
			step.x++;
		}
		step.y++;
	}
}

void	draw_lines(t_editor *editor, t_eline *lines)
{
	t_eline		*iterator;

	iterator = lines;
	while (iterator)
	{
		draw_eline(editor, *iterator->points[0]->coord,\
		*iterator->points[1]->coord, iterator->color);
		iterator = iterator->next;
	}
}

void		draw_vertical_line(t_editor *editor, int x, int from, int to)
{

	while (from > to)
	{
		put_epixel(editor, x, from, 0x02dec1);
		from--;
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

void		draw_square(t_editor *editor, t_esprite *sprite)
{
	// t_coords	step;
	t_coords	max;
	t_coords	iter;

	// ft_printf("1\n");
	sprite->size = SPRITE_SIZE * editor->zoom;
	sprite->dist.x = (sprite->origin.x + sprite->move.x) * editor->zoom;
	sprite->dist.y = (sprite->origin.y + sprite->move.y) * editor->zoom;
	max.x = sprite->coord->x + sprite->dist.x + sprite->size / 2;
	max.y = sprite->coord->y + sprite->dist.y + sprite->size / 2;
	iter.y = sprite->coord->y + sprite->dist.y - sprite->size / 2;
	// step.x =
	// ft_printf("2\n");
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

void        draw_rooms(t_editor *editor)
{
	t_room	*iterate_room;

	iterate_room = editor->rooms;
	while (iterate_room)
	{
		draw_texture_room(editor, iterate_room);
		draw_sprite(editor, iterate_room->sprites);
		draw_lines(editor, iterate_room->lines);
		iterate_room = iterate_room->next;		
	}
}
