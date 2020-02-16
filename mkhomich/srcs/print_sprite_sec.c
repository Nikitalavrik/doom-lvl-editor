/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprite_sec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:42:22 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/17 14:42:22 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	print_sp(t_doom *doom, int p_x, int p_y, int sp, int z, int pl)
{
	SDL_Rect win;

	if (doom->sp[sp].count > doom->sp[sp].frame - 1)
		doom->sp[sp].count = 0;
	win.x = p_x - ((int)(doom->sp[sp].text[doom->sp[sp].count].w *
	doom->sp[sp].zoom) >> 1);
	win.y = p_y - doom->sp[sp].text[doom->sp[sp].count].h * doom->sp[sp].zoom;
	win.w = (int)(doom->sp[sp].text[doom->sp[sp].count].w * doom->sp[sp].zoom);
	win.h = (int)(doom->sp[sp].text[doom->sp[sp].count].h * doom->sp[sp].zoom);
	z_buffsprite(win, &doom->sp[sp].text[doom->sp[sp].count], doom, z, pl);
}

void	pr_s(t_doom *doom, int c, int nb)
{
	if (doom->sec[nb].sp[c].nb_sp == 12)
		doom->sp[doom->sec[nb].sp[c].nb_sp].zoom =
		(1 / doom->sec[nb].sp[c].sp.tz2) * ((float)doom->w / 256);
	if (doom->sec[nb].sp[c].nb_sp == 13)
		doom->sp[doom->sec[nb].sp[c].nb_sp].zoom =
		(1 / doom->sec[nb].sp[c].sp.tz2) * ((float)doom->w / 500);
	if (doom->sec[nb].sp[c].nb_sp == 14)
		doom->sp[doom->sec[nb].sp[c].nb_sp].zoom =
		(1 / doom->sec[nb].sp[c].sp.tz2) * ((float)doom->w / 90);
	if (doom->sec[nb].sp[c].nb_sp == 15)
		doom->sp[doom->sec[nb].sp[c].nb_sp].zoom =
		(1 / doom->sec[nb].sp[c].sp.tz2) * ((float)doom->w / 80);
	if (doom->sec[nb].sp[c].nb_sp == 17)
		doom->sp[doom->sec[nb].sp[c].nb_sp].zoom =
				(1 / doom->sec[nb].sp[c].sp.tz2) * ((float)doom->w / 1000);
    if (doom->sec[nb].sp[c].nb_sp == 19)
        doom->sp[doom->sec[nb].sp[c].nb_sp].zoom =
                (1 / doom->sec[nb].sp[c].sp.tz2) * ((float)doom->w / 300);
	print_sp(doom, doom->sec[nb].sp[c].sp.tx1, doom->sec[nb].sp[c].sp.ty1,
	doom->sec[nb].sp[c].nb_sp,
	((1 << FIXP28_SHIFT) / doom->sec[nb].sp[c].sp.tz2), nb);
	doom->sec[nb].sp[c].time = SDL_GetTicks();
}

void	print_sp_arm(t_doom *doom, int c, int nb)
{
	if (doom->sec[nb].sp[c].nb_sp == 13)
		if (doom->play[doom->n_play].armor < 34)
		{
			doom->play[doom->n_play].armor += 17;
			if (doom->play[doom->n_play].armor > 34)
				doom->play[doom->n_play].armor = 34;
			doom->sec[nb].sp[c].viem = 0;
		}
	if (doom->sec[nb].sp[c].nb_sp == 14)
		if (doom->play[doom->n_play].heart < 34)
		{
			doom->play[doom->n_play].heart += 17;
			if (doom->play[doom->n_play].heart > 34)
				doom->play[doom->n_play].heart = 34;
			doom->sec[nb].sp[c].viem = 0;
		}
	if (doom->sec[nb].sp[c].nb_sp == 15)
		if (doom->play[doom->n_play].shot < 8)
		{
			doom->play[doom->n_play].shot = 8;
			doom->sec[nb].sp[c].viem = 0;
		}
}

void	print_sp_sec(t_doom *doom)
{
	int		nb;
	int		c;
	float	line;

	nb = -1;
	while (++nb < doom->max_s)
	{
		if (doom->sec[nb].max_sp > 0)
		{
			c = -1;
			while (++c < doom->sec[nb].max_sp)
			{
				if (doom->sec[nb].sp[c].sp.tz2 > 0.4
				&& doom->sec[nb].sp[c].viem)
					pr_s(doom, c, nb);
				else if (doom->sec[nb].sp[c].viem == 0 &&
				((SDL_GetTicks() - doom->sec[nb].sp[c].time) > 20000))
					doom->sec[nb].sp[c].viem = 1;
				if (doom->sec[nb].sp[c].take && doom->sec[nb].sp[c].viem)
				{
					line = sqrt((doom->sec[nb].sp[c].sp.tx2 *
					doom->sec[nb].sp[c].sp.tx2) + (doom->sec[nb].sp[c].sp.tz2
					* doom->sec[nb].sp[c].sp.tz2));
					if (line < 2)
						print_sp_arm(doom, c, nb);
				}
			}
		}
	}
}
