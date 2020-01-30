/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:47:48 by nlavrine          #+#    #+#             */
/*   Updated: 2020/01/30 13:57:04 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		free_doom(t_doom *doom)
{
	int	i;
	int	j;

	if (doom->max_s && doom->max_t)
	{
		i = -1;
		j = -1;
		while (++i < doom->max_s)
		{
			ft_memdel((void **)&doom->sec[i].pts);
			if (doom->sec[i].max_sp)
				ft_memdel((void **)&doom->sec[i].sp);
			// while ((int)doom->sec[i].tex_y > 0 && (++j < doom->sec[i].tex_y + 1))
			// 	ft_memdel((void **)&doom->sec[i].toch[j]);
			ft_memdel((void **)&doom->sec[i].toch);
		}
		ft_memdel((void **)&doom->sec);
		// system("leaks editor")
		ft_memdel((void **)&doom->play);
		ft_memdel((void **)&doom->rend);
		ft_memdel((void **)&doom->toch);
	}
}
