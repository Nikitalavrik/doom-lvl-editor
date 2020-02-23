/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:35:30 by nlavrine          #+#    #+#             */
/*   Updated: 2020/02/23 17:39:37 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_editor.h"

void		grid_all_sec(t_editor *editor)
{
	int	i;

	i = 0;
	while (i < editor->max_sectors)
	{
		grid_sec(editor->doom, &editor->doom->sec[i], -50);
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
	editor->doom->play[0].t.y = editor->doom->toch[0].y;
	editor->doom->play[0].t.z = (editor->doom->toch[0].z + editor->doom->toch[1].z) / 2;;
	editor->doom->play[0].angle_x = 0;
	editor->doom->play[0].angle_y = 270;
	editor->doom->play[0].speed = 1;
}

void		editor_autosave(t_editor *editor)
{
	char *tmp;

	tmp = ft_strjoin("saves/", editor->filename);
	ft_printf("save to %s\n", tmp);
	save_map(editor->doom, tmp);
	ft_memdel((void **)&tmp);
}

void		d3_init(t_editor *editor)
{
	// ft_printf("max_s = %i max_t = %i\n", editor->doom->max_s, editor->doom->max_t);
	free_doom(editor->doom);	
	editor->doom->max_t = editor->max_sectors * 4;
	editor->doom->max_s = editor->max_sectors;
	ft_printf("max_s = %i\n", editor->doom->max_s);
	if (editor->doom->max_s)
	{
		editor->doom->sec = (t_sec*)ft_memalloc(sizeof(t_sec) * editor->doom->max_s);
		editor->doom->toch = (t_toch*)ft_memalloc(sizeof(t_toch) * editor->doom->max_t);
		convert_rooms(editor);
		editor->doom->rend = (t_render*)ft_memalloc(sizeof(t_render) * editor->doom->max_s);
		grid_all_sec(editor);
		put_player(editor);
		editor->flags.t_f.visual = 1;
	}
}
