/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:41:35 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/12 13:38:17 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

/*
** get coords nearest editor->coords
*/

t_coords	get_coords(t_editor *editor, t_coords mouse)
{
	t_coords	coord;
	double		sq_zoom;

	sq_zoom = SQUARE_SIZE * editor->zoom;
	coord.x = ((mouse.x + editor->center.x + (int)(2 * editor->zoom)) +\
	(mouse.x + editor->center.x + (int)(2 * editor->zoom))) / 2 / sq_zoom;
	coord.y = ((mouse.y + editor->center.y + (int)(2 * editor->zoom)) +\
	(mouse.y + editor->center.y + (int)(2 * editor->zoom))) / 2 / sq_zoom;

	if (coord.x > 0 && coord.x < editor->size.x &&\
		coord.y > 0 && coord.y < editor->size.y)
		return (coord);
	else
	{
		coord.x = INT16_MAX;
		return (coord);
	}
}

/*
** calc dist from mouse to line
*/

double		calc_short_dist(t_eline *line, t_coords mouse)
{
	t_dcoords	line_a_b;
	t_dcoords	dist_c_s;
	double		h;

	line_a_b.x = pow(mouse.x - line->points[0]->coord->x, 2)\
	+ pow(mouse.y - line->points[0]->coord->y, 2);
	line_a_b.y = pow(mouse.x - line->points[1]->coord->x, 2)\
	+ pow(mouse.y - line->points[1]->coord->y, 2);
	dist_c_s.x = pow(line->points[1]->coord->x - line->points[0]->coord->x, 2)\
	+ pow(line->points[1]->coord->y\
	- line->points[0]->coord->y, 2);
	dist_c_s.y = abs((mouse.x - line->points[1]->coord->x) *\
	(line->points[0]->coord->y - line->points[1]->coord->y) -\
	(line->points[0]->coord->x - line->points[1]->coord->x) *\
	(mouse.y - line->points[1]->coord->y));
	h = 2 * dist_c_s.y / sqrt(dist_c_s.x);
	if ((line_a_b.x + dist_c_s.x) < line_a_b.y\
	|| (line_a_b.y + dist_c_s.x) < line_a_b.x)
	{
		if (line_a_b.x < line_a_b.y)
			return (sqrt(line_a_b.x));
		if (line_a_b.y < line_a_b.x)
			return (sqrt(line_a_b.y));
	}
	return (h);
}
