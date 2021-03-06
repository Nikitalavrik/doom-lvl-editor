/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:37:16 by nlavrine          #+#    #+#             */
/*   Updated: 2019/11/29 17:01:08 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_editor.h"

int		alpha_grad(int color1, int color2, unsigned char a)
{
	int		transform;
	int		r;
	int		g;
	int		b;

	r = ((unsigned char)(color1 >> 16) * a) / 255 +\
	((unsigned char)(color2 >> 16) * (255 - a)) / 255;
	g = ((unsigned char)(color1 >> 8) * a) / 255 +\
	((unsigned char)(color2 >> 8) * (255 - a)) / 255;
	b = ((unsigned char)(color1) * a) / 255 +\
	((unsigned char)(color2) * (255 - a)) / 255;
	transform = a;
	transform = (transform << 8) | r;
	transform = (transform << 8) | g;
	transform = (transform << 8) | b;
	return (transform);
}

void	sprites_alpha(t_esprite *spr)
{
	if (spr->flag_a)
	{
		if (spr->alpha < 190)
			spr->alpha += 10;
	}
	else
	{
		if (spr->alpha > 140)
			spr->alpha -= 10;
	}
}

void	rooms_alpha(t_room *iter)
{
	if (iter->flags.t_f.select || iter->flags.t_f.hover)
	{
		if (iter->alpha < 170)
			iter->alpha += 10;
	}
	else
	{
		if (iter->alpha > 80)
			iter->alpha -= 10;
	}
}

void	check_alpha(t_editor *editor)
{
	t_esprite	*spr;
	t_room		*iter;

	iter = editor->rooms;
	while (iter)
	{
		rooms_alpha(iter);
		spr = iter->sprites;
		while (spr)
		{
			sprites_alpha(spr);
			spr = spr->next;
		}
		iter = iter->next;
	}
}
