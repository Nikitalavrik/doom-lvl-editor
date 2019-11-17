/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/17 20:01:54 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		keyboard_events_down(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (1);
	else if (event.key.keysym.sym == SDLK_s)
		editor->flags.t_f.select = editor->flags.t_f.select ? 0 : 1;
	else if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 1;
	else if (editor->flags.t_f.lctrl && event.key.keysym.sym == SDLK_z)
	{
		pop_line(&editor->lines);
		pop_point(&editor->point);
	}
	else if (event.key.keysym.sym == SDLK_SPACE && editor->point)
		close_room(editor);
	// else if (event.key.keysym.sym == SDLK_c)
	// 	editor->flags.t_f.select
	return (0);
}

int		keyboard_events_up(t_editor *editor, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LCTRL)
		editor->flags.t_f.lctrl = 0;
	return (0);
}

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

void	mouse_event(t_editor *editor, SDL_Event	event)
{
	t_coords 	mouse_position;
	double		sq_zoom;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	sq_zoom = SQUARE_SIZE * editor->zoom;
	if (event.wheel.y > 0 && editor->zoom < 20)
	{
		editor->center.x = ((mouse_position.x + editor->center.x) / sq_zoom) *\
		(SQUARE_SIZE * (editor->zoom * 1.02)) - mouse_position.x;
		editor->center.y = ((mouse_position.y + editor->center.y) / sq_zoom)*\
		(SQUARE_SIZE * (editor->zoom * 1.02)) - mouse_position.y;
		editor->zoom *= 1.02;
	}
	else if (event.wheel.y < 0 && editor->zoom > 0.16)
	{
		editor->center.x = ((mouse_position.x + editor->center.x) / sq_zoom) *\
		(SQUARE_SIZE * (editor->zoom * 0.95)) - mouse_position.x;
		editor->center.y = ((mouse_position.y + editor->center.y) / sq_zoom)*\
		(SQUARE_SIZE * (editor->zoom * 0.95)) - mouse_position.y;
		editor->zoom *= 0.95;
	}
}

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
			editor->selected = editor->selected == iter ? NULL : editor->selected;
		}
		else if (type && iter->flags.t_f.select)
		{
			iter->flags.t_f.select = 0;
		}
		iter = iter->next;
	}
	iter = editor->selected;
	if (iter)
	{
		iter = iter->prev;
		while (iter)
		{
			iter->flags.t_f.select = 0;
			iter->flags.t_f.hover = 0;
			iter = iter->prev;
		}
	}

}

void	mouse_motion(t_editor *editor)
{
	t_coords 	mouse_position;
	t_coords	coord;
	t_coords	*finded;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	coord = get_coords(editor, mouse_position);
	if (editor->finded)
		editor->finded->inc = 0;
	if (coord.x != INT16_MAX)
	{
		finded = &editor->coords[coord.y][coord.x];
		if (mouse_position.x <= finded->x + (int)(finded->r * editor->zoom) &&\
			mouse_position.x >= finded->x - (int)(finded->r * editor->zoom) &&\
			mouse_position.y <= finded->y + (int)(finded->r * editor->zoom) &&\
			mouse_position.y >= finded->y - (int)(finded->r * editor->zoom))
			{
				finded->inc = 1;
				finded->r = 3;
				editor->finded = finded;
			}
	}
	if (editor->rooms)
		check_rooms(editor, mouse_position, 0);
	if (editor->lines || editor->selected)
		check_line(editor, mouse_position);
}

void	mouse_move_map(t_editor *editor)
{
	t_coords 	mouse_position;
	t_coords	tmp_calc;
	t_coords	limit;

	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	if ((mouse_position.x != editor->move_save.x ||\
		mouse_position.y != editor->move_save.y))
	{
		limit.x = SQUARE_SIZE * editor->size.x * editor->zoom - editor->width + MENU_WIDTH + PADDING_WIDTH;
		limit.y = SQUARE_SIZE * editor->size.y * editor->zoom - editor->height;
		tmp_calc.x = mouse_position.x - editor->move_save.x;
		tmp_calc.y = mouse_position.y - editor->move_save.y;
		if ((editor->center.x > 0 ||  tmp_calc.x < 0) &&\
		(editor->center.x < limit.x || tmp_calc.x > 0))
			editor->center.x -= tmp_calc.x;
		if ((editor->center.y > 0 || tmp_calc.y < 0) &&\
		(editor->center.y < limit.y || tmp_calc.y > 0))
			editor->center.y -= tmp_calc.y;
		editor->move_save.x = mouse_position.x;
		editor->move_save.y = mouse_position.y;;
	}
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

int		detect_event(t_editor *editor)
{
	t_coords 	mouse_position;
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_MOUSEWHEEL)
			mouse_event(editor, event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
			editor->flags.t_f.move = editor->flags.t_f.select;
			editor->move_save.x = mouse_position.x;
			editor->move_save.y = mouse_position.y;
			check_rooms(editor, mouse_position, 1);
			if (!editor->flags.t_f.select)
				add_line(editor);
		}
		if (event.type == SDL_MOUSEBUTTONUP && editor->flags.t_f.move)
			editor->flags.t_f.move = 0;
		if (editor->flags.t_f.move)
			mouse_move_map(editor);
		if (event.type == SDL_MOUSEMOTION)
			mouse_motion(editor);
		if (event.type == SDL_KEYDOWN)
			if (keyboard_events_down(editor, event))
				return (1);
		if (event.type == SDL_KEYUP)
			if (keyboard_events_up(editor, event))
				return (1);
	}
	return (0);
}
