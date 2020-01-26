/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uron.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:26:58 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/17 14:26:59 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

int		how_zone(t_doom *doom, int pl, int zone, int ur)
{
	if (zone == 3)
	{
		ur = (doom->play[pl].armor == 0) ? 8 : 5;
		doom->play[pl].armor -= 7;
	}
	else if (zone == 4)
	{
		ur = (doom->play[pl].armor == 0) ? 2 : 1;
		doom->play[pl].armor -= 1;
	}
	return (ur);
}

void	calc_uron_pl(t_doom *doom, int pl, int zone, int weap)
{
	int ur;

	ur = 0;
	if (pl == doom->n_play)
		SDL_FillRect(doom->surface, NULL, 0xff0000);
	if (zone == 1)
	{
		ur = (doom->play[pl].armor == 0) ? 17 : 9;
		doom->play[pl].armor -= 10;
	}
	else if (zone == 2)
	{
		ur = (doom->play[pl].armor == 0) ? 12 : 7;
		doom->play[pl].armor -= 9;
	}
	else
		ur = how_zone(doom, pl, zone, ur);
	doom->play[pl].heart -= (ur / ((weap == 7 || weap == 8) ? 1 : 2));
	if (doom->play[pl].heart < 0)
		doom->play[pl].heart = 0;
	if (doom->play[pl].armor < 0)
		doom->play[pl].armor = 0;
}

void	calc_uron_aim(t_doom *doom, t_play play)
{
	int nb;

	nb = 0;
	if (play.f_move == 2 && play.aim.zone != 0 && play.count == 2 &&
	doom->nb % 10 == 0 && doom->move.altern == 0)
		doom->play[doom->n_play].aim.pull = 1;
	else if (play.aim.zone != 0 && doom->nb % 10 == 0 &&
	play.weapons == 6 && doom->move.altern)
		doom->play[doom->n_play].aim.pull = 2;
	else
		doom->play[doom->n_play].aim.pull = 0;
	nb = -1;
	while (++nb < doom->max_p)
	{
		if (doom->play[nb].aim.pl == doom->n_play &&
		doom->play[nb].aim.zone != 0 && doom->play[nb].aim.pull == 1)
			calc_uron_pl(doom, doom->n_play,
			doom->play[nb].aim.zone, doom->play[nb].weapons);
		else if (doom->play[nb].aim.pl == doom->n_play
		&& doom->play[nb].aim.pull == 2)
			calc_uron_pl(doom, doom->n_play, 4, doom->play[nb].weapons);
	}
}

void	calc_uron(t_doom *doom)
{
	t_play	play;

	play = doom->play[doom->n_play];
	if (doom->mult == 0)
	{
		if (play.f_move == 2 && play.aim.zone != 0 && play.count == 2
		&& doom->nb % 10 == 0)
			calc_uron_pl(doom, play.aim.pl, play.aim.zone, play.weapons);
		else if (play.aim.zone != 0 && doom->nb % 10 == 0 && doom->move.altern
		&& play.weapons == 6)
			if (size_line(doom->play[play.aim.pl].t.x - play.t.x,
			doom->play[play.aim.pl].t.z - play.t.z) < 5)
				calc_uron_pl(doom, play.aim.pl, 4, play.weapons);
	}
	else if (doom->mult)
		calc_uron_aim(doom, play);
}
