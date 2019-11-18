/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:55:10 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/18 18:13:17 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"


double		calc_short_dist(t_line *line, t_coords mouse)
{
	double a;
	double b;
	double c;
	double s;
	double h;

	a = pow(mouse.x - line->points[0]->coord->x, 2) + pow(mouse.y - line->points[0]->coord->y, 2);
	b = pow(mouse.x - line->points[1]->coord->x, 2) + pow(mouse.y - line->points[1]->coord->y, 2);
	c = pow(line->points[1]->coord->x - line->points[0]->coord->x, 2) + pow(line->points[1]->coord->y\
	- line->points[0]->coord->y, 2);
	s = abs((mouse.x  - line->points[1]->coord->x) * (line->points[0]->coord->y - line->points[1]->coord->y) -\
	(line->points[0]->coord->x  - line->points[1]->coord->x) * (mouse.y - line->points[1]->coord->y));
	h = 2 * s / sqrt(c);
	if ((a + c) < b || (b + c) < a)
	{
		if (a < b)
			return (sqrt(a));
		if (b < a)
			return (sqrt(b));
	}
	return (h);
}

void	check_line(t_editor *editor, t_coords mouse)
{
	double		calc_dist;
	double		min_dist;
	t_line		*choosen;
	t_line		*lines;

	lines = editor->selected ? editor->selected->lines : editor->lines;
	min_dist = 20;
	choosen = NULL;
	while (lines)
	{
		lines->color = WALL_COLOR;
		calc_dist = calc_short_dist(lines, mouse);	
		if (calc_dist < min_dist)
		{
			min_dist = calc_dist;
			choosen = lines;
		}
		lines = lines->next;
	}
	if (choosen)
		choosen->color = PRESS_WALL_COLOR;
}

void	check_rooms(t_editor *editor, t_coords mouse, int type)
{
	t_coords	min;
	t_coords	max;
	t_room		*iter;
	int			min_area;

	iter = editor->rooms;
	min_area = INT16_MAX;
	while (iter && iter->next)
		iter = iter->next;
	while (iter)
	{
		min = editor->coords[iter->min_xy.y][iter->min_xy.x];
		max = editor->coords[iter->max_xy.y][iter->max_xy.x];
		iter->flags.t_f.hover = 0;
		if (mouse.x >= min.x && mouse.x <= max.x\
		&& mouse.y >= min.y && mouse.y <= max.y &&\
		iter->area < min_area)
		{
			iter->flags.t_f.hover = 1;
			min_area = iter->area;
			if (type)
			{
				iter->flags.t_f.select = 1;
				editor->selected = iter;
			}
		}
		else if (type && editor->selected && iter->flags.t_f.select)
		{
			iter->flags.t_f.select = 0;
			editor->flags.t_f.sprite = 0;
			// ft_printf("111\n");
			editor->selected = editor->selected == iter ? NULL : editor->selected;
		}
		iter = iter->prev;
	}
	iter = editor->selected;
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
				editor->line_cnt++;
				if (editor->line_cnt >= 2 && editor->point && editor->point->next)
				{
					editor->line_cnt = 1;
					push_line(&editor->lines, editor->point, editor->point->next);
					editor->lines->color = WALL_COLOR;
					editor->lines->id = editor->line_id;
					editor->line_id++;
				}
			}
	}
}

/*
** check nearest sprite
*/

int		check_sprites(t_sprite *sprites, t_coords mouse, double zoom)
{
	int			dist;
	t_sprite	*iter;

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
				// ft_printf("zoom %f\n", editor->zoom);
				push_sprite(&editor->selected->sprites, &editor->coords[coord.y][coord.x]);
				editor->selected->sprites->origin.x = (mouse.x -\
				editor->coords[coord.y][coord.x].x) / editor->zoom;
				editor->selected->sprites->origin.y = (mouse.y -\
				editor->coords[coord.y][coord.x].y) / editor->zoom;
				editor->selected->sprites->size = SPRITE_SIZE * editor->zoom;
				editor->selected->sprites->alpha = 140;
			}
		}
	}
}
