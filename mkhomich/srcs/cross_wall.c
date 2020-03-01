/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:42:38 by tbratsla          #+#    #+#             */
/*   Updated: 2020/03/01 13:42:39 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

int		check_cross(t_cross a, t_cross b, t_cross c, t_cross d)
{
	double	Ua;
	double	Ub;
	int		numerator_a;
	int		numerator_b;
	int		denominator;
    
    denominator = (d.y-c.y)*(a.x-b.x)-(d.x-c.x)*(a.y-b.y);
    if (denominator == 0)
    {
		if ( (a.x * b.y - b.x * a.y) * (d.x - c.x) - (c.x * d.y - d.x * c.y) *\
		(b.x - a.x) == 0 && (a.x * b.y - b.x * a.y) * (d.y - c.y) -\
		(c.x * d.y - d.x * c.y) * (b.y - a.y) == 0)
            return (1);
        return (0);
    }
    else
    {
		numerator_a = (d.x - b.x) * (d.y - c.y) - (d.x - c.x) * (d.y - b.y);
		numerator_b = (a.x - b.x) * (d.y - b.y) - (d.x - b.x) * (a.y - b.y);
		Ua = numerator_a / denominator;
		Ub = numerator_b / denominator;
		if (Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1)
			return (1);
		return (0);
    }
    return (0);
}

int		check_wall_crossing(t_doom *doom, int nb, int i)
{
	t_cross a;
	t_cross b;
	t_cross c;
	t_cross d;

	a.x = doom->play[nb].t.x;
	a.y = doom->play[nb].t.y;
	b.x = doom->play[doom->n_play].t.x;
	b.x = doom->play[doom->n_play].t.y;
	c.x = doom->toch[doom->sec[i].pts[0]].x;
	c.y = doom->toch[doom->sec[i].pts[0]].z;
	d.x = doom->toch[doom->sec[i].pts[3]].x;
	d.y = doom->toch[doom->sec[i].pts[3]].z;
	return (check_cross(a, b, c, d));
}
