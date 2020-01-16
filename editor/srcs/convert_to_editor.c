/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:44:13 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/12 17:30:13 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	load_to_editor(t_editor *editor, char *filename)
{
	partly_free_editor(editor);
	free_doom(editor->doom);
	load_map(editor->doom, filename);
	convert_doom_to_editor(editor, editor->doom);
}

void	convert_sec_to_line(t_editor *editor, t_doom *doom, int i)
{
	t_coords coord;

	coord.x = (int)doom->toch[i * 4].x >> CONVERT_ZOOM;
	coord.y = (int)doom->toch[i * 4].z >> CONVERT_ZOOM;
	push_point(&editor->rooms->point, &editor->coords[coord.y][coord.x]);
	editor->rooms->point->x = coord.x;
	editor->rooms->point->y = coord.y;
	coord.x = (int)doom->toch[i * 4 + 2].x >> CONVERT_ZOOM;
	coord.y = (int)doom->toch[i * 4 + 2].z >> CONVERT_ZOOM;
	push_point(&editor->rooms->point, &editor->coords[coord.y][coord.x]);
	editor->rooms->point->x = coord.x;
	editor->rooms->point->y = coord.y;
	push_line(&editor->lines, editor->rooms->point, editor->rooms->point->next);
	editor->lines->color = WALL_COLOR;
	editor->lines->begin_height = (int)doom->toch[i * 4].y;
	editor->lines->height = (int)doom->toch[i * 4 + 2].y;
	editor->lines->num_of_textures = doom->sec[i].t_full;
}

void	convert_floor_to_room(t_editor *editor, t_doom *doom, int i)
{
	int			s;
	t_coords	coord;
	t_coords	origin;

	push_room(&editor->rooms, NULL);
	editor->rooms->min_xy.x = (int)doom->toch[i * 4].x >> CONVERT_ZOOM;
	editor->rooms->max_xy.y = (int)doom->toch[i * 4].z >> CONVERT_ZOOM;
	editor->rooms->min_xy.y = (int)doom->toch[i * 4 + 1].z >> CONVERT_ZOOM;
	editor->rooms->max_xy.x = (int)doom->toch[i * 4 + 2].x >> CONVERT_ZOOM;
	editor->rooms->alpha = 80;
	editor->rooms->area = pow(editor->rooms->max_xy.x - editor->rooms->min_xy.x, 2) +\
	pow(editor->rooms->max_xy.y - editor->rooms->min_xy.y, 2);
	editor->num_of_rooms++;
	s = 0;
	while (s < doom->sec[i].max_sp)
	{
		origin.x = ((int)doom->sec[i].sp[s].sp.x) >> CONVERT_ZOOM;
		origin.y = ((int)doom->sec[i].sp[s].sp.z) >> CONVERT_ZOOM;
		coord = get_coords(editor, origin);
		push_sprite(&editor->rooms->sprites, &editor->coords[origin.y][origin.x]);
		editor->rooms->sprites->origin.x = ((((unsigned int)doom->sec[i].sp[s].sp.x << (32 - CONVERT_ZOOM)) >> (32 - CONVERT_ZOOM)) + doom->sec[i].sp[s].sp.x - (int)doom->sec[i].sp[s].sp.x) * 4;
		editor->rooms->sprites->origin.y = ((((unsigned int)doom->sec[i].sp[s].sp.z << (32 - CONVERT_ZOOM)) >> (32 - CONVERT_ZOOM)) + doom->sec[i].sp[s].sp.z - (int)doom->sec[i].sp[s].sp.z) * 4;
		editor->rooms->sprites->size = SPRITE_SIZE * editor->zoom;
		editor->rooms->sprites->alpha = 140;
		editor->rooms->sprites->x = origin.x;
		editor->rooms->sprites->y = origin.y;
		editor->rooms->max_sprites++;
		s++;
	}
}

void	convert_doom_to_editor(t_editor *editor, t_doom *doom)
{
	int 		i;

	i = 0;
	editor->max_sectors = doom->max_s;
	while (i < doom->max_s)
	{
		if (!doom->sec[i].tape)
			convert_floor_to_room(editor, doom, i);
		else if (editor->rooms)
			convert_sec_to_line(editor, doom, i);
		else
		{
			ft_printf("Seems like a trouble in converting -_-\n");
			break ;
		}
		i++;
	}
	if (editor->rooms)
	{
		sort_rooms(&editor->rooms, editor->num_of_rooms);
		editor->center.x = (editor->rooms->min_xy.x + editor->rooms->max_xy.x) / 2\
		* SQUARE_SIZE * editor->zoom - (editor->width - MENU_WIDTH) / 2;
		editor->center.y = (editor->rooms->min_xy.y + editor->rooms->max_xy.y) / 2\
		* SQUARE_SIZE * editor->zoom - (editor->height) / 2;
	}
}