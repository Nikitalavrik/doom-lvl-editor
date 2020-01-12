/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:35:30 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 15:48:07 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_editor.h"

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

void		editor_autosave(t_doom *doom)
{
	char *filename;
	char *num;

	num = ft_itoa((unsigned short int)&doom);
	filename = ft_strjoin("saves/", num);
	ft_printf("save to %s\n", filename);
	save_map(doom, filename);
	ft_memdel((void **)&filename);
	ft_memdel((void **)&num);
}

void		d3_init(t_editor *editor)
{
	free_doom(editor->doom);
	editor->doom->max_t = editor->max_sectors * 4;
	editor->doom->max_s = editor->max_sectors;
	ft_printf("max_s = %i max_t = %i\n", editor->doom->max_s, editor->doom->max_t);
	if (editor->doom->max_s)
	{
		editor->doom->sec = ft_memalloc(sizeof(t_sec) * editor->doom->max_s);
		editor->doom->toch = ft_memalloc(sizeof(t_toch) * editor->doom->max_t);
		convert_rooms(editor);
		editor->doom->rend = ft_memalloc(sizeof(t_render) * editor->doom->max_s);
		grid_all_sec(editor);
		put_player(editor);
		editor->flags.t_f.visual = 1;
		editor_autosave(editor->doom);
	}
}