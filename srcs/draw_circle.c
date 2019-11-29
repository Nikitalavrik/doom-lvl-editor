/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:36:13 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 16:04:58 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	drawCircle(t_editor *editor, t_coords coord0, t_coords coord1, int color) 
{ 
    put_epixel(editor, coord0.x + coord1.x, coord0.y + coord1.y, color); 
    put_epixel(editor, coord0.x - coord1.x, coord0.y + coord1.y, color); 
    put_epixel(editor, coord0.x + coord1.x, coord0.y - coord1.y, color); 
    put_epixel(editor, coord0.x - coord1.x, coord0.y - coord1.y, color); 
    put_epixel(editor, coord0.x + coord1.y, coord0.y + coord1.x, color); 
    put_epixel(editor, coord0.x - coord1.y, coord0.y + coord1.x, color); 
    put_epixel(editor, coord0.x + coord1.y, coord0.y - coord1.x, color); 
    put_epixel(editor, coord0.x - coord1.y, coord0.y - coord1.x, color); 
} 

void	circle_Bres(t_editor *editor, t_coords coord0, int color) 
{
	int 		d;
	int			r;
	t_coords	coord1;

	r = (int)(coord0.r * editor->zoom);
	coord1.x = 0;
	coord1.y = r;
	d = 3 - 2 * r;
    drawCircle(editor, coord0, coord1 , color); 
    while (coord1.y >= coord1.x) 
    {
        coord1.x++; 
        if (d > 0) 
        { 
            coord1.y--;  
            d = d + 4 * (coord1.x - coord1.y) + 10; 
        } 
        else
            d = d + 4 * coord1.x + 6; 
        drawCircle(editor, coord0, coord1 , color);  
    } 
} 

void	draw_cells(t_editor *editor)
{
	t_coords	step;

	step.y = 0;
	coords_rerange(editor);
	while (step.y < editor->size.y)
	{
		step.x = 0;
		while (step.x < editor->size.x)
		{
			circle_Bres(editor, editor->coords[step.y][step.x], STANDART_COLOR);
			step.x++;
		}
		step.y++;
	}
}
