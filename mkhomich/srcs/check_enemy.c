/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:57:09 by tbratsla          #+#    #+#             */
/*   Updated: 2020/02/25 17:57:10 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

int		check_way(t_doom *doom, int nb)
{
	int	i;

	i = 0;
	while (i < doom->max_s)
	{
		if (doom->sec[i].tape == 1)
			if (check_wall_crossing(doom, nb, i))
				return (1);
		i++;
	}
	return (0);
}

int		check_enemy(t_doom *doom, int nb, long *leng)
{
	int			x;
	int			y;

	x = doom->play[nb].t.x - doom->play[doom->n_play].t.x;
	y = doom->play[nb].t.z - doom->play[doom->n_play].t.z;
	*leng = x * x + y * y;
	if (((*leng > 1000 && doom->play[nb].angle_sp <= 6 &&\
		doom->play[nb].angle_sp >= 3) || (*leng > 2000 &&\
		doom->play[nb].angle_sp >= 6 &&\
		doom->play[nb].angle_sp <= 3)) || check_way(doom, nb))
	{
		doom->flag.t_f1.see = 0;
		return (0);
	}
	vec_play(doom, nb);
	if (doom->play[nb].angle_sp == 0)
		return (2);
	return (1);
}

void	bots_logic(t_doom *doom, int nb)
{
	int		state;
	long	len;
	int		zone;

	state = 0;
	while ((state = check_enemy(doom, nb, &len)) == 1)
 		doom->play[nb].angle_y += 1;
 	if (state == 2 && len <= 900)
 		doom->play[nb].f_move = 2;
 	else
 		doom->play[nb].f_move = 1;
 	if (doom->play[nb].f_move == 2 && doom->play[nb].count == 0 &&\
 		doom->flag.t_f1.fire == 0)
 	{
 		zone = rand() % 32;
 		if (zone >= 1 && zone <= 4)
 			calc_uron_pl(doom, doom->n_play, zone, 1);
		doom->flag.t_f1.fire	= 1;
 	}
 	if (doom->play[nb].f_move == 2 && doom->play[nb].count != 0)
 		doom->flag.t_f1.fire = 0;
}
