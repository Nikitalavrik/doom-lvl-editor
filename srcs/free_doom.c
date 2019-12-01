/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:47:48 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 15:48:13 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

void		free_doom(t_doom *doom)
{
	int	i;

	if (doom->max_s && doom->max_t)
	{
		// ft_printf("free max_s = %i max_t = %i\n", doom->max_s, doom->max_t);
		ft_memdel((void **)&doom->toch);
		i = -1;
		while (++i < doom->max_s)
		{
			ft_memdel((void **)&doom->sec[i].pts);
			if (doom->sec[i].max_sp)
				ft_memdel((void **)&doom->sec[i].sp);
		}
		ft_memdel((void **)&doom->sec);
		// system("leaks editor")
		ft_memdel((void **)&doom->play);
		ft_memdel((void **)&doom->rend);
	}
}