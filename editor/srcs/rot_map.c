/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:47:06 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/30 13:54:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	rot_y(t_editor *editor, t_coords *coord)
{
	int		x;

	x = coord->x;
	coord->x = editor->absolute_center.x + (x - editor->absolute_center.x) * cos(editor->left_right)\
											+ coord->z * sin(editor->left_right);
	coord->z = -(x - editor->absolute_center.x) * sin(editor->left_right)\
											+ coord->z * cos(editor->left_right);
}

void	rot_x(t_editor *editor, t_coords *coord)
{
	int y;

	y = coord->y;
	coord->y = editor->absolute_center.y + (y - editor->absolute_center.y) * cos(editor->up_down)\
											+ coord->z * sin(editor->up_down);
	coord->z = -(y - editor->absolute_center.y) * sin(editor->up_down)\
											+ coord->z * cos(editor->up_down);
}

void	change_view(t_editor *editor)
{
	int	x;
	int	y;

	y = 0;
	while (y < editor->size.y)
	{
		x = 0;
		while (x < editor->size.x)
		{
			rot_x(editor, &editor->coords[y][x]);
			rot_y(editor, &editor->coords[y][x]);
			x++;
		}
		y++;
	}
}
