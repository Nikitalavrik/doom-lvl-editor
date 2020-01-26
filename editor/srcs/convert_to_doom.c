/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_doom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:44:41 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/26 17:55:07 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		parse_walls(t_editor *editor, t_eline *lines, int *i, int *r)
{
	t_eline *iter;

	iter = lines;
	while (iter)
	{
		editor->doom->toch[++(*i)].x = iter->points[0]->x << CONVERT_ZOOM;
		editor->doom->toch[*i].z = iter->points[0]->y << CONVERT_ZOOM;
		editor->doom->toch[*i].y = iter->begin_height;
		editor->doom->sec[++(*r)].max_toch = 4;
		iter->id = *r;
		editor->doom->sec[*r].pts = (int*)ft_memalloc(sizeof(int) *\
		editor->doom->sec[*r].max_toch);
		editor->doom->sec[*r].pts[0] = *i;
		editor->doom->toch[++(*i)].x = (iter->points[2]->x << CONVERT_ZOOM) + iter->points[2]->rot_x;
		editor->doom->toch[*i].z = (iter->points[2]->y << CONVERT_ZOOM) + iter->points[2]->rot_y;
		editor->doom->toch[*i].y = iter->begin_height + iter->height;
		editor->doom->sec[*r].pts[1] = *i;
		editor->doom->toch[++(*i)].x = (iter->points[3]->x << CONVERT_ZOOM) + iter->points[3]->rot_x;
		editor->doom->toch[*i].z = (iter->points[3]->y << CONVERT_ZOOM) + iter->points[3]->rot_y;
		editor->doom->toch[*i].y = iter->begin_height + iter->height;
		editor->doom->sec[*r].pts[2] = *i;
		editor->doom->toch[++(*i)].x = iter->points[1]->x << CONVERT_ZOOM;
		editor->doom->toch[*i].z = iter->points[1]->y << CONVERT_ZOOM;
		editor->doom->toch[*i].y = iter->begin_height;
		editor->doom->sec[*r].pts[3] = *i;
		editor->doom->sec[*r].level = iter->floor;
		editor->doom->sec[*r].t_full = iter->num_of_textures;
		editor->doom->sec[*r].t_win = 0;
		editor->doom->sec[*r].tape = 1;
		iter = iter->next;
	}
}

void		parse_sprites(t_editor *editor, t_esprite *sprites, int sec, int s)
{
	editor->doom->sec[sec].sp[s].nb_sp = sprites->num_of_textures;
	editor->doom->sec[sec].sp[s].sp.x = (sprites->x << CONVERT_ZOOM) +\
	(sprites->origin.x + sprites->move.x) / 4;
	editor->doom->sec[sec].sp[s].sp.z = (sprites->y << CONVERT_ZOOM) +\
	(sprites->origin.y + sprites->move.y) / 4;
	editor->doom->sec[sec].sp[s].sp.y = sprites->floor * FLOOR_HEIGHT;
	editor->doom->sec[sec].sp[s].viem = 1;
	editor->doom->sec[sec].sp[s].take = 0;
}

void		init_floor(t_editor *editor, t_room *room, int *i, int *r)
{
	int			s;
	t_esprite	*sprites;

	s = 0;
	sprites = room->sprites;
	editor->doom->toch[++(*i)].x = room->min_xy.x << CONVERT_ZOOM;
	editor->doom->toch[*i].z = room->max_xy.y << CONVERT_ZOOM;
	editor->doom->toch[*i].y = room->height;
	editor->doom->sec[++(*r)].max_toch = 4;
	room->id = *r;
	editor->doom->sec[*r].pts = ft_memalloc(sizeof(int) *\
	editor->doom->sec[*r].max_toch);
	editor->doom->sec[*r].pts[0] = *i;
	editor->doom->toch[++(*i)].x = room->min_xy.x << CONVERT_ZOOM;
	editor->doom->toch[*i].z = room->min_xy.y << CONVERT_ZOOM;
	editor->doom->toch[*i].y = room->height;
	editor->doom->sec[*r].pts[1] = *i;
	editor->doom->toch[++(*i)].x = room->max_xy.x << CONVERT_ZOOM;
	editor->doom->toch[*i].z = room->min_xy.y << CONVERT_ZOOM;
	editor->doom->toch[*i].y = room->height;
	editor->doom->sec[*r].pts[2] = *i;
	editor->doom->toch[++(*i)].x = room->max_xy.x << CONVERT_ZOOM;
	editor->doom->toch[*i].z = room->max_xy.y << CONVERT_ZOOM;
	editor->doom->toch[*i].y = room->height;
	editor->doom->sec[*r].pts[3] = *i;
	editor->doom->sec[*r].level = room->floor;
	editor->doom->sec[*r].t_full = room->num_of_textures;
	editor->doom->sec[*r].t_win = 0;
	editor->doom->sec[*r].tape = 0;
	editor->doom->sec[*r].max_sp = room->max_sprites;
	ft_printf("spr = %i\n", editor->doom->sec[*r].max_sp);
	if (editor->doom->sec[*r].max_sp)
	{
		editor->doom->sec[*r].sp = ft_memalloc(sizeof(t_tochsp) *\
		editor->doom->sec[*r].max_sp);		
	}

	while (sprites)
	{
		parse_sprites(editor, sprites, *r, s);
		sprites = sprites->next;
		s++;
	}
}

void		convert_rooms(t_editor *editor)
{
	int		i;
	int		r;
	t_room 	*iter;

	i = -1;
	r = -1;
	iter = editor->rooms;
	while (iter)
	{
		init_floor(editor, iter, &i, &r);
		iter = iter->next;
	}
	parse_walls(editor, editor->lines, &i, &r);
}
