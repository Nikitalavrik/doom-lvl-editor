/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:47:48 by nlavrine          #+#    #+#             */
/*   Updated: 2020/03/01 13:43:12 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		free_sec(t_sec *sec)
{
	int	y;
	int	x;

	y = -1;
	while (++y < sec->tex_y + 1)
	{
		x = -1;
		ft_memdel((void **)&sec->toch[y]);
		while (++x < sec->tex_x + 1)
		{
			if (y * sec->tex_w + x < sec->tex_w * sec->tex_h)
			{
				ft_memdel((void **)&sec->l_map[y * sec->tex_w + x]);
				ft_memdel((void **)&sec->tex[y * sec->tex_w + x]);
			}
		}
	}
	ft_memdel((void **)&sec->toch);
	// system("leaks editor");
	ft_memdel((void **)&sec->tex);
	ft_memdel((void **)&sec->l_map);
}

void		free_doom(t_doom *doom)
{
	int	i;
	
	doom->max_p = 0;
	if (doom->max_s && doom->max_t)
	{
		i = -1;
		while (++i < doom->max_s)
		{
			ft_memdel((void **)&doom->sec[i].pts);
			if (doom->sec[i].max_sp)
				ft_memdel((void **)&doom->sec[i].sp);
			free_sec(&doom->sec[i]);
		}
		ft_memdel((void **)&doom->sec);
		// system("leaks editor")
		ft_memdel((void **)&doom->play);
		ft_memdel((void **)&doom->rend);
		ft_memdel((void **)&doom->toch);
	}
	// system("leaks editor");
}
