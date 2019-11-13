/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:55:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/13 17:32:38 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	put_pixel(t_editor *editor, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH - MENU_WIDTH && y >= 0 && y < HEIGHT)
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

void		draw_line(t_editor *editor, t_coords coord0,
										t_coords coord1, int color)
{
	t_coords	coord;
	t_coords	delta;
	t_coords	iter;
	t_coords	error;

	coord = calc_delta(coord0, coord1, &delta, &iter);
	error.x = delta.x + delta.y;
	while (1 && coord0.x > 0 && coord0.y > 0)
	{
		put_pixel(editor, coord.x, coord.y, color);
		if ((coord.x == coord1.x || coord.x < 0)\
						&& (coord.y == coord1.y || coord.y < 0))
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
    put_pixel(editor, coord0.x + coord1.x, coord0.y + coord1.y, color); 
    put_pixel(editor, coord0.x - coord1.x, coord0.y + coord1.y, color); 
    put_pixel(editor, coord0.x + coord1.x, coord0.y - coord1.y, color); 
    put_pixel(editor, coord0.x - coord1.x, coord0.y - coord1.y, color); 
    put_pixel(editor, coord0.x + coord1.y, coord0.y + coord1.x, color); 
    put_pixel(editor, coord0.x - coord1.y, coord0.y + coord1.x, color); 
    put_pixel(editor, coord0.x + coord1.y, coord0.y - coord1.x, color); 
    put_pixel(editor, coord0.x - coord1.y, coord0.y - coord1.x, color); 
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
	int			color;
	t_coords	step;

	step.y = 0;
	color = 0xbdb5b5;
	coords_rerange(editor);
	while (step.y < editor->size.y)
	{
		step.x = 0;
		while (step.x < editor->size.x)
		{
			circle_Bres(editor, editor->coords[step.y][step.x], color);
			step.x++;
		}
		step.y++;
	}
}

void	draw_lines(t_editor *editor)
{
	t_point	*iterator;

	iterator = editor->point;
	while (iterator && iterator->next)
	{
		draw_line(editor, *iterator->coord, *iterator->next->coord, 0x8f017e);
		iterator = iterator->next;
	}
}

void        draw_rooms(t_editor *editor)
{
	t_room	*iterate_room;
	t_point	*iterator;

	iterate_room = editor->rooms;
	while (iterate_room)
	{
		iterator = iterate_room->point;
		while (iterator && iterator->next)
		{
			draw_line(editor, *iterator->coord,
						*iterator->next->coord, 0x8f017e);
			iterator = iterator->next;
		}
		iterate_room = iterate_room->next;		
	}
}
