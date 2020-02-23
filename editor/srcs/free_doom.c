/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:47:48 by nlavrine          #+#    #+#             */
/*   Updated: 2020/02/23 17:04:45 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		free_doom(t_doom *doom)
{
	int	i;
	int	y;
	int x;
	
	if (doom->max_s && doom->max_t)
	{
		i = -1;
		while (++i < doom->max_s)
		{
			ft_memdel((void **)&doom->sec[i].pts);
			if (doom->sec[i].max_sp)
				ft_memdel((void **)&doom->sec[i].sp);
			y = -1;
			while (++y < doom->sec[i].tex_y + 1)
			{
				x = -1;
				ft_memdel((void **)&doom->sec[i].toch[y]);
				while (++x < doom->sec[i].tex_x + 1)
				{
					if (y * doom->sec[i].tex_w + x < doom->sec[i].tex_w * doom->sec[i].tex_h)
					{
						ft_memdel((void **)&doom->sec[i].l_map[y * doom->sec[i].tex_w + x]);
						ft_memdel((void **)&doom->sec[i].tex[y * doom->sec[i].tex_w + x]);
					}
				}
			}
			
			ft_memdel((void **)&doom->sec[i].toch);
			// system("leaks editor");
			ft_memdel((void **)&doom->sec[i].tex);
			ft_memdel((void **)&doom->sec[i].l_map);
			// system("leaks editor");
		}
		ft_memdel((void **)&doom->sec);
		// system("leaks editor")
		ft_memdel((void **)&doom->play);
		ft_memdel((void **)&doom->rend);
		ft_memdel((void **)&doom->toch);
	}
	// system("leaks editor");
}
