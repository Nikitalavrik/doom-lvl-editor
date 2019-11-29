/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:32:57 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 15:34:25 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

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

void	draw_stick_line(t_editor *editor)
{
	if (editor->stick_line)
	{
		draw_eline(editor, *editor->stick_line->points[0]->coord,
		*editor->stick_line->points[1]->coord, editor->stick_line->color);
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
