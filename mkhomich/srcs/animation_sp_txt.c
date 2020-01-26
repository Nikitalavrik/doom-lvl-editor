/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_sp_txt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:33:01 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/17 10:33:02 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	lava_cpy(int *dst, int *src, size_t n)
{
	while (n > 0)
	{
		dst[n - 1] = src[n - 1];
		n--;
	}
}

void	lava(t_text *lava, t_doom *doom)
{
	int y;

	y = 0;
	lava_cpy(doom->buff, &lava->tex[lava->w * (lava->h - 1)], lava->w);
	while (y < lava->h - 1)
	{
		lava_cpy(&lava->tex[lava->w * (lava->h - 1 - y)],
		&lava->tex[lava->w * (lava->h - 2 - y)], lava->w);
		y++;
	}
	lava_cpy(lava->tex, doom->buff, lava->w);
}

void	ani_sp_shot(t_doom *doom, int pl)
{
	doom->play[pl].angle_sp = 32;
	if (doom->nb % 10 == 0)
	{
		if (doom->play[pl].count == 2)
			doom->play[pl].aim.pull = 1;
		doom->play[pl].count++;
	}
	if (doom->play[pl].count >= 3)
	{
		doom->play[pl].count = 0;
		doom->play[doom->n_play].f_move = 0;
	}
}

void	ani_sp(t_doom *doom, int pl)
{
	doom->play[pl].aim.pull = 0;
	if (doom->play[pl].f_move == 0)
		doom->play[pl].count = 0;
	else if (doom->play[pl].f_move == 1)
	{
		if (doom->nb % 10 == 0)
			doom->play[pl].count++;
		if (doom->play[pl].count >= 4)
			doom->play[pl].count = 0;
	}
	else if (doom->play[pl].f_move == 2)
		ani_sp_shot(doom, pl);
	else if (doom->play[pl].f_move == 3)
	{
		doom->play[pl].angle_sp = 35;
		if (doom->nb % 15 == 0 && doom->play[pl].count <= 6)
			doom->play[pl].count++;
	}
}
