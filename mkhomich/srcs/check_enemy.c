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


static	int	vertical_line(t_doom *doom, t_way pr)
{
	int err;
	int	sign_x;
	int	sign_y;
	int del_x;
	int del_y;

	doom = (void *)doom;
	sign_y = pr.y1 >= pr.y0 ? 1 : -1;
	sign_x = pr.x1 >= pr.x0 ? 1 : -1;
	del_x = abs(pr.x1 - pr.x0);
	del_y = abs(pr.y1 - pr.y0);
	err = -del_y;
	while (pr.x0 != pr.x1 || pr.y0 != pr.y1)
	{
		if (1)
			return (0);
		pr.y0 += sign_y;
		err += 2 * del_x;
		if (err > 0)
		{
			err -= 2 * del_y;
			pr.x0 += sign_x;
		}
	}
	return (0);
}

static	int	horizontal_line(t_doom *doom, t_way pr)
{
	int err;
	int	sign_y;
	int	sign_x;
	int del_x;
	int del_y;

	doom = (void *)doom;
	sign_y = pr.y1 >= pr.y0 ? 1 : -1;
	sign_x = pr.x1 >= pr.x0 ? 1 : -1;
	del_x = abs(pr.x1 - pr.x0);
	del_y = abs(pr.y1 - pr.y0);
	err = -del_x;
	while (pr.x0 != pr.x1 || pr.y0 != pr.y1)
	{
		if (1)
			return (0);
		pr.x0 += sign_x;
		err += 2 * del_y;
		if (err > 0)
		{
			err -= 2 * del_x;
			pr.y0 += sign_y;
		}
	}
	return (0);
}


int		check_way(t_doom *doom, int nb)
{
	int		del_x;
	int		del_y;
	int		res;
	t_way	pr;

	pr.x0 = doom->play[doom->n_play].t.x;
	pr.y0 = doom->play[doom->n_play].t.y;
	pr.x1 = doom->play[nb].t.x;
	pr.y1 = doom->play[nb].t.y;
	res = 0;
	del_x = abs(pr.x1 - pr.x0);
	del_y = abs(pr.y1 - pr.y0);
	if (del_y <= del_x)
		res += horizontal_line(doom, pr);
	else
		res += vertical_line(doom, pr);
	return (res);
}

int		check_enemy(t_doom *doom, int nb)
{
	long long	leng;
	int			x;
	int			y;

	x = doom->play[nb].t.x - doom->play[doom->n_play].t.x;
	y = doom->play[nb].t.y - doom->play[doom->n_play].t.y;
	leng = x * x + y * y;
	if (((leng > 1000 && doom->play[nb].angle_sp <= 6 &&\
		doom->play[nb].angle_sp >= 3) || (leng > 2000 &&\
		doom->play[nb].angle_sp >= 6 &&\
		doom->play[nb].angle_sp <= 3)) || check_way(doom, nb))
		return (0);
	vec_play(doom, nb);
	if (doom->play[nb].angle_sp == 0)
		return (2);
	return (1);
}

void	bots_logic(t_doom *doom, int nb)
{
	int	state;

	state = 0;
	while ((state = check_enemy(doom, nb)) == 1)
 		doom->play[nb].angle_y += 1;
 	if (state == 2)
 	{
 		// write fire fuctions;
 	}
}
