/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:11:24 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/17 11:11:24 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	print_aim(t_doom *doom)
{
	int x;
	int y;
	int size;

	size = 14;
	x = doom->x_aim - (size / 2);
	y = doom->y_aim;
	while (x <= doom->igr_x + (size / 2))
	{
		put_pixel(doom, x, y, 0xFFFFFF);
		x++;
	}
	x = doom->x_aim;
	y = doom->y_aim - (size / 2);
	while (y <= doom->h * 0.62 + (size / 2))
	{
		put_pixel(doom, x, y, 0xFFFFFF);
		y++;
	}
}

void	print_weapons(t_doom *doom)
{
	if (doom->play[doom->n_play].weapons == 6 && doom->move.altern == 0)
		print_sprite(doom, doom->w * 0.65, doom->h, 6, 0, 0);
	else if (doom->play[doom->n_play].weapons == 6 && doom->move.altern)
	{
		print_sprite(doom, doom->w * 0.65, doom->h, 16, 0, 0);
		doom->sp[16].count++;
	}
	if (doom->play[doom->n_play].weapons == 7)
		print_sprite(doom, doom->w * 0.82, doom->h, 7, 0, 0);
	if (doom->play[doom->n_play].weapons == 8)
		print_sprite(doom, doom->igr_x, doom->h, 8, 0, 0);
}

float    anim_hud(t_doom *doom, float base, float cof)
{
    if (doom->nb > 10 && doom->nb < 20)
			doom->sp[0].zoom = base + cof;
    if (doom->nb > 20 && doom->nb < 30)
			doom->sp[0].zoom = base;
    if (doom->nb > 30 && doom->nb < 40)
			doom->sp[0].zoom = base + cof;
    if (doom->nb > 40 && doom->nb < 80)
			doom->sp[0].zoom = base;
    return base;
}

void	print_hud(t_doom *doom)
{
    float buff;

    buff = anim_hud(doom, doom->sp[0].zoom, doom->sp[0].zoom * 0.2);
	if ((doom->sp[2].count = doom->play[doom->n_play].heart) > 0)
	{
		print_sprite(doom, doom->w * 0.05, doom->h * 0.95, 0, 0, 0);
		print_sprite(doom, doom->w * 0.05, doom->h * 0.98, 1, 0, 0);
		print_sprite(doom, doom->w * 0.15, doom->h * 0.96, 2, 0, 0);
	}
	if ((doom->sp[4].count = doom->play[doom->n_play].armor) > 0)
	{
		print_sprite(doom, doom->w * 0.3, doom->h * 0.98, 3, 0, 0);
		print_sprite(doom, doom->w * 0.43, doom->h * 0.96, 4, 0, 0);
	}
	doom->sp[5].count = doom->play[doom->n_play].shot - 1;
	if (doom->play[doom->n_play].shot)
		print_sprite(doom, doom->w * 0.91, doom->h * 0.97, 5, 0, 0);
    doom->sp[0].zoom = buff;
}

void	check_mob_sp(t_doom *doom, int nb)
{
	if (doom->play[nb].sp == 9)
		doom->sp[9].zoom = (1 / doom->play[nb].t.tz2) * ((float)doom->w / 250);
	if (doom->play[nb].sp == 10)
		doom->sp[10].zoom = (1 / doom->play[nb].t.tz2) * ((float)doom->w / 33);
	if (doom->play[nb].sp == 11)
		doom->sp[11].zoom = (1 / doom->play[nb].t.tz2) * ((float)doom->w / 33);
}

void	print_mob(t_doom *doom)
{
	int nb;

	nb = -1;
	doom->play[doom->n_play].aim.pl = 0;
	doom->play[doom->n_play].aim.zone = 0;
	while (++nb < doom->max_p)
	{
		if (doom->play[nb].heart == 0)
			doom->play[nb].f_move = 3;
		if (doom->mult == 2 || doom->mult == 0 || nb == doom->n_play)
			ani_sp(doom, nb);
		if (doom->n_play != nb)
		{
			if (doom->play[nb].t.tz2 > 0.4)
			{
				check_mob_sp(doom, nb);
				ani_sp(doom, nb);
				print_sprite(doom, doom->play[nb].t.tx1, doom->play[nb].t.ty1,
				doom->play[nb].sp, ((1 << FIXP28_SHIFT) / doom->play[nb].t.tz2), nb);
			}
		}
	}
}
