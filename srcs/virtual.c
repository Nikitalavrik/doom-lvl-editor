/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:35:30 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/22 18:30:56 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_editor.h"

void		print_toch(t_editor *editor, int i)
{
	int k;

	k = 0;
	while (k <= i)
	{
		ft_printf("toch[%03i].x = %3.f toch[%03i].y = %3.f  toch[%03i].z = %03.f\n", 
		k, editor->doom->toch[k].x,
		k, editor->doom->toch[k].y,
		k, editor->doom->toch[k].z);
		k++;
	}
}

void		parse_walls(t_editor *editor, t_eline *lines, int *i, int *r)
{
	t_eline *iter;

	iter = lines;
	while (iter)
	{
		editor->doom->toch[++(*i)].x = iter->points[0]->coord->x;
		editor->doom->toch[*i].y = iter->points[0]->coord->y;
		editor->doom->toch[*i].z = 0;
		editor->doom->sec[++(*r)].max_toch = 4;
		editor->doom->sec[*r].pts = (int*)ft_memalloc(sizeof(int) * editor->doom->sec[*r].max_toch);
		editor->doom->sec[*r].pts[0] = *i;
		editor->doom->toch[++(*i)].x = iter->points[0]->coord->x;
		editor->doom->toch[*i].y = iter->points[0]->coord->y;
		editor->doom->toch[*i].z = 200;
		editor->doom->sec[*r].pts[1] = *i;
		editor->doom->toch[++(*i)].x = iter->points[1]->coord->x;
		editor->doom->toch[*i].y = iter->points[1]->coord->y;
		editor->doom->toch[*i].z = 0;
		editor->doom->sec[*r].pts[2] = *i;
		editor->doom->toch[++(*i)].x = iter->points[1]->coord->x;
		editor->doom->toch[*i].y = iter->points[1]->coord->y;
		editor->doom->toch[*i].z = 200;
		editor->doom->sec[*r].pts[3] = *i;
		editor->doom->sec[*r].t_full = 1;
		editor->doom->sec[*r].t_win = 0;
		editor->doom->sec[*r].tape = 1;
		iter = iter->next;
	}
}

void		parse_sprites(t_editor *editor, t_esprite *sprites, int sec, int s)
{
	editor->doom->sec[sec].sp[s].nb_sp = 12; // xz chto eto
	editor->doom->sec[sec].sp[s].sp.x = sprites->origin.x;
	editor->doom->sec[sec].sp[s].sp.y = sprites->origin.y;
	editor->doom->sec[sec].sp[s].sp.z = 2;
	editor->doom->sec[sec].sp[s].viem = 1;
	editor->doom->sec[sec].sp[s].take = 0;
}

void		init_floor(t_editor *editor, t_room *room, int *i, int *r)
{
	int			s;
	t_esprite	*sprites;

	s = 0;
	sprites = room->sprites;
	editor->doom->toch[++(*i)].x = editor->coords[room->min_xy.y][room->min_xy.x].x;
	editor->doom->toch[*i].y = editor->coords[room->min_xy.y][room->min_xy.x].y;
	editor->doom->toch[*i].z = 0;
	editor->doom->sec[++(*r)].max_toch = 4;
	editor->doom->sec[*r].pts = (int*)ft_memalloc(sizeof(int) * editor->doom->sec[*r].max_toch);
	editor->doom->sec[*r].pts[0] = *i;
	editor->doom->toch[++(*i)].x = editor->coords[room->max_xy.y][room->min_xy.x].x;
	editor->doom->toch[*i].y = editor->coords[room->max_xy.y][room->min_xy.x].y;
	editor->doom->sec[*r].pts[1] = *i;
	editor->doom->toch[++(*i)].x = editor->coords[room->min_xy.y][room->max_xy.x].x;
	editor->doom->toch[*i].y = editor->coords[room->min_xy.y][room->max_xy.x].y;
	editor->doom->sec[*r].pts[2] = *i;
	editor->doom->toch[++(*i)].x = editor->coords[room->max_xy.y][room->max_xy.x].x;
	editor->doom->toch[*i].y = editor->coords[room->max_xy.y][room->max_xy.x].y;
	editor->doom->sec[*r].pts[3] = *i;
	editor->doom->sec[*r].t_full = 1;
	editor->doom->sec[*r].t_win = 0;
	editor->doom->sec[*r].tape = 0;
	editor->doom->sec[*r].max_sp = room->max_sprites;
	editor->doom->sec[*r].sp = ft_memalloc(sizeof(t_tochsp) * editor->doom->sec[*r].max_sp);
	while (sprites)
	{
		parse_sprites(editor, sprites, *r, s);
		sprites = sprites->next;
		s++;
	}
}

void		parse_rooms(t_editor *editor)
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
		parse_walls(editor, iter->lines, &i, &r);
		iter = iter->next;
	}
	// print_toch(editor, i);
}

void		grid_all_sec(t_editor *editor)
{
	int	i;

	i = 0;
	while (i < editor->max_sectors)
	{
		grid_sec(editor->doom, &editor->doom->sec[i]);
		i++;
	}
}

void		put_player(t_editor *editor)
{
	t_room *room;

	room = editor->rooms;
	editor->doom->max_p = 1;
	editor->doom->play = ft_memalloc(sizeof(t_play));
	editor->doom->play[0].t.x = 10;
	editor->doom->play[0].t.y = 20;
	editor->doom->play[0].t.z = 10;
	editor->doom->play[0].angle_x = 0;
	editor->doom->play[0].angle_y = 270;
	editor->doom->play[0].speed = 0.2f;
}

void		d3_init(t_editor *editor)
{
	editor->doom = ft_memalloc(sizeof(t_doom));
	editor->doom->max_t = editor->max_sectors * 4;
	editor->doom->max_s = editor->max_sectors;
	editor->doom->x_aim = IGRX;
	editor->doom->y_aim = HEIGHT * 0.62;
	editor->doom->gravity = 0.015;
	ft_printf("max_t = %i max_s = %i\n", editor->doom->max_t, editor->doom->max_s);
	if (editor->rooms)
	{
		editor->doom->sec = ft_memalloc(sizeof(t_sec) * editor->doom->max_s);
		editor->doom->rend = ft_memalloc(sizeof(t_render) * editor->doom->max_s);
		editor->doom->toch = ft_memalloc(sizeof(t_toch) * editor->doom->max_t);
		parse_rooms(editor);
		grid_all_sec(editor);
		put_player(editor);
		editor->doom->z_buffer = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);
	}
}
