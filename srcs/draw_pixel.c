/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:33:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 15:34:10 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		get_epixel(t_editor *editor, int x, int y)
{
	if (x >= 0 && x < E_WIDTH - MENU_WIDTH && y >= 0 && y < E_HEIGHT)
		return (((int *)editor->surf->pixels)[(y * editor->surf->w) + x]);
	return (-1);
}

void	put_epixel(t_editor *editor, int x, int y, int color)
{
	if (x >= 0 && x < E_WIDTH - MENU_WIDTH && y >= 0 && y < E_HEIGHT)
		((int *)editor->surf->pixels)[(y * editor->surf->w) + x] = color;
}
