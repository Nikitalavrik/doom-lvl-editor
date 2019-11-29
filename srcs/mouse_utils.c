/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:41:35 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:02:35 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

/*
** get coords nearest editor->coords
*/

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
