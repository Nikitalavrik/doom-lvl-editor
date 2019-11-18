/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:40:18 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/18 13:34:10 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void	print_coords(t_coords **coords, int max_y, int max_x)
{
	int	x;
	int	y;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			ft_printf("%i ", coords[y][x].x);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void	print_room(t_room *begin)
{
	t_room *iter;

	iter = begin;
	while (iter)
	{
		ft_printf("area = %i\n", iter->area);
		iter = iter->next;	
	}
	ft_printf("~~~~~~~~~~~~~~~~~~\n");
}
