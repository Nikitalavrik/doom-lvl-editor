/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:33:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/12/28 17:43:04 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		get_epixel(t_editor *editor, int x, int y)
{
	if (x >= 0 && x < editor->width - MENU_WIDTH && y >= 0 && y < editor->height)
		return (((int *)editor->surf->pixels)[(y * editor->surf->w) + x]);
	return (-1);
}

void	put_epixel(t_editor *editor, int x, int y, int color)
{
	if (x >= 0 && x < editor->width - MENU_WIDTH && y >= 0 && y < editor->height)
		((int *)editor->surf->pixels)[(y * editor->surf->w) + x] = color;
}
