/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:35:30 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/24 19:52:38 by nlavrine         ###   ########.fr       */
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
		editor->doom->toch[++(*i)].x = iter->points[0]->x << 4;
		editor->doom->toch[*i].z = iter->points[0]->y << 4;
		editor->doom->toch[*i].y = 0;
		editor->doom->sec[++(*r)].max_toch = 4;
		editor->doom->sec[*r].pts = (int*)ft_memalloc(sizeof(int) * editor->doom->sec[*r].max_toch);
		editor->doom->sec[*r].pts[0] = *i;
		editor->doom->toch[++(*i)].x = iter->points[0]->x << 4;
		editor->doom->toch[*i].z = iter->points[0]->y << 4;
		editor->doom->toch[*i].y = 50;
		editor->doom->sec[*r].pts[1] = *i;
		editor->doom->toch[++(*i)].x = iter->points[1]->x << 4;
		editor->doom->toch[*i].z = iter->points[1]->y << 4;
		editor->doom->toch[*i].y = 50;
		editor->doom->sec[*r].pts[2] = *i;
		editor->doom->toch[++(*i)].x = iter->points[1]->x << 4;
		editor->doom->toch[*i].z = iter->points[1]->y << 4;
		editor->doom->toch[*i].y = 0;
		editor->doom->sec[*r].pts[3] = *i;
		editor->doom->sec[*r].t_full = 14;
		editor->doom->sec[*r].t_win = 0;
		editor->doom->sec[*r].tape = 1;
		iter = iter->next;
	}
}

void		parse_sprites(t_editor *editor, t_esprite *sprites, int sec, int s)
{
	editor->doom->sec[sec].sp[s].nb_sp = 12;
	editor->doom->sec[sec].sp[s].sp.x = (sprites->x << 4) + (sprites->origin.x + sprites->move.x) / 2;
	editor->doom->sec[sec].sp[s].sp.z = (sprites->y << 4) + (sprites->origin.y + sprites->move.y) / 2;
	editor->doom->sec[sec].sp[s].sp.y = 1;
	editor->doom->sec[sec].sp[s].viem = 1;
	editor->doom->sec[sec].sp[s].take = 0;
}

void		init_floor(t_editor *editor, t_room *room, int *i, int *r)
{
	int			s;
	t_esprite	*sprites;

	s = 0;
	sprites = room->sprites;
	editor->doom->toch[++(*i)].x = room->min_xy.x << 4;
	editor->doom->toch[*i].z = room->max_xy.y << 4;
	editor->doom->sec[++(*r)].max_toch = 4;
	editor->doom->sec[*r].pts = (int*)ft_memalloc(sizeof(int) * editor->doom->sec[*r].max_toch);
	editor->doom->sec[*r].pts[0] = *i;
	editor->doom->toch[++(*i)].x = room->min_xy.x << 4;
	editor->doom->toch[*i].z = room->min_xy.y << 4;
	editor->doom->sec[*r].pts[1] = *i;
	editor->doom->toch[++(*i)].x = room->max_xy.x << 4;
	editor->doom->toch[*i].z = room->min_xy.y << 4;
	editor->doom->sec[*r].pts[2] = *i;
	editor->doom->toch[++(*i)].x = room->max_xy.x << 4;
	editor->doom->toch[*i].z = room->max_xy.y << 4;
	editor->doom->sec[*r].pts[3] = *i;
	editor->doom->sec[*r].t_full = 8;
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
	editor->doom->play[0].t.x = (editor->doom->toch[0].x + editor->doom->toch[3].x) / 2;
	editor->doom->play[0].t.y = 0;
	editor->doom->play[0].t.z = (editor->doom->toch[0].z + editor->doom->toch[1].z) / 2;;
	editor->doom->play[0].angle_x = 0;
	editor->doom->play[0].angle_y = 270;
	editor->doom->play[0].speed = 1;
}

void		d3_init(t_editor *editor)
{
	editor->doom = ft_memalloc(sizeof(t_doom));
	editor->doom->max_t = editor->max_sectors * 4;
	editor->doom->max_s = editor->max_sectors;
	// ft_printf("max_s = %i max_t = %i\n", editor->doom->max_s, editor->doom->max_t);
	editor->doom->x_aim = IGRX;
	editor->doom->y_aim = HEIGHT * 0.62;
	editor->doom->gravity = 0.015;
	editor->doom->min_z = 0.5;
	// if (editor->rooms)
	// {
		editor->doom->sec = ft_memalloc(sizeof(t_sec) * editor->doom->max_s);
		editor->doom->toch = ft_memalloc(sizeof(t_toch) * editor->doom->max_t);
		parse_rooms(editor);
		// load_map(editor->doom);
		editor->doom->rend = ft_memalloc(sizeof(t_render) * editor->doom->max_s);
		grid_all_sec(editor);
		put_player(editor);
		editor->doom->z_buffer = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);
		init_skybox(editor->doom);
		load_texture_wall(editor->doom);
		editor->doom->window = editor->win;
		editor->doom->surface = editor->surf;
		editor->flags.t_f.visual = editor->flags.t_f.visual ? 0 : 1;
	// }
	save_map(editor->doom);
}
