/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:50:47 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/30 14:07:06 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		coords_init(t_editor *editor, t_coords *size)
{
	t_coords	iterator;
	t_coords	**coords;

	size->x = 200;
	size->y = 150;
	coords = ft_memalloc(sizeof(t_coords *) * size->y);
	iterator.y = 0;
	while (iterator.y < size->y)
	{
		coords[iterator.y] = ft_memalloc(sizeof(t_coords) * size->x);
		iterator.y++;
	}
	editor->coords = coords;
}

void		coords_rerange(t_editor *editor)
{
	t_coords	iterator;

	iterator.y = 0;
	while (iterator.y < editor->size.y)
	{
		iterator.x = 0;
		while (iterator.x < editor->size.x)
		{
			editor->coords[iterator.y][iterator.x].x = (int)(iterator.x *\
			SQUARE_SIZE * editor->zoom) - editor->center.x;
			editor->coords[iterator.y][iterator.x].y = (int)(iterator.y *\
			SQUARE_SIZE * editor->zoom) - editor->center.y;
			editor->coords[iterator.y][iterator.x].z = 0;
			if (!editor->coords[iterator.y][iterator.x].color)
				editor->coords[iterator.y][iterator.x].color = STANDART_COLOR;
			if (!editor->coords[iterator.y][iterator.x].inc)
				editor->coords[iterator.y][iterator.x].r = 2;
			iterator.x++;
		}
		iterator.y++;
	}
	change_view(editor);
}
