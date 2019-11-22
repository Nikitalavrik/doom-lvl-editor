/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:35:30 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/22 16:16:58 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_editor.h"

void		print_toch(t_editor *editor, int i)
{
	int k;

	k = 0;
	while (k < i)
	{
		ft_printf(" k = %i x = %f y = %f z = %f\n", k, editor->doom->toch[k].x, editor->doom->toch[k].y, editor->doom->toch[k].z);
		k++;
	}
}

void		parse_walls(t_editor *editor, t_eline *lines, int *i)
{
	t_eline *iter;

	iter = lines;
	while (iter)
	{
		editor->doom->toch[*i].x = iter->points[0]->coord->x;
		editor->doom->toch[*i].y = iter->points[0]->coord->y;
		editor->doom->toch[*i].z = 0;
		// ft_printf("x = %f y = %i z = %i\n", editor->doom->toch[*i].x, editor->doom->toch[*i].y, editor->doom->toch[*i].z);
		editor->doom->toch[++(*i)].x = iter->points[0]->coord->x;
		editor->doom->toch[*i].y = iter->points[0]->coord->y;
		editor->doom->toch[*i].z = 200;
		// ft_printf("x = %i y = %i z = %i\n", editor->doom->toch[*i].x, editor->doom->toch[*i].y, editor->doom->toch[*i].z);
		editor->doom->toch[++(*i)].x = iter->points[1]->coord->x;
		editor->doom->toch[*i].y = iter->points[1]->coord->y;
		editor->doom->toch[*i].z = 0;
		// ft_printf("x = %i y = %i z = %i\n", editor->doom->toch[*i].x, editor->doom->toch[*i].y, editor->doom->toch[*i].z);
		editor->doom->toch[++(*i)].x = iter->points[1]->coord->x;
		editor->doom->toch[*i].y = iter->points[1]->coord->y;
		editor->doom->toch[*i].z = 200;
		// ft_printf("x = %i y = %i z = %i\n", editor->doom->toch[*i].x, editor->doom->toch[*i].y, editor->doom->toch[*i].z);
		iter = iter->next;
	}
}

void		parse_room(t_editor *editor)
{
	int		i;
	t_room 	*iter;

	i = 0;
	iter = editor->rooms;
	while (iter)
	{
		// init_floor(editor, iter);
		parse_walls(editor, iter->lines, &i);
		iter = iter->next;
	}
	print_toch(editor, i);
}

void		d3_init(t_editor *editor)
{
	// if (!editor->doom)
	editor->doom = ft_memalloc(sizeof(t_doom));
	editor->doom->max_t = 96; // need to init in lines create
	editor->doom->max_s = 28;
	// exit(0);
	if (editor->rooms)
	{
		// editor->doom->sec = ft_memalloc(sizeof(t_sec) * editor->doom->max_s);
		// editor->doom->rend = ft_memalloc(sizeof(t_render) * editor->doom->max_s);
		// ft_printf("mx_t %i mx_s %i\n", editor->doom.max_t, editor->doom.max_s);
		editor->doom->toch = ft_memalloc(sizeof(t_toch) * editor->doom->max_t);
		parse_room(editor);
	}
}
