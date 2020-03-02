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

double		max_cross(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double		min_cross(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

void	swap_cross(t_cross *a, t_cross *b)
{
	int x;
	int	y;

	x = a->x;
	y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = x;
	b->y = y;
}

int		check_cross(t_cross a, t_cross b, t_cross c, t_cross d)
{
    double a1;
	double a2;
	double b1;
	double b2;
	double xa;

    if (a.x > b.x)
    	swap_cross(&a, &b);
    if (c.x > d.x)
    	swap_cross(&c, &d);
    if (b.x < c.x)
    	return (0);
    if ((a.x - b.x == 0) && (c.x - d.x == 0))
    {
    	if (a.x == c.x)
    	{
    		if (!((max_cross(a.y, b.y) < min_cross(c.y, d.y)) ||
                (min_cross(a.y, b.y) > max_cross(c.y, d.y))))
                return (1);
    	}
    	return (0);
    }
    if (a.x - b.x == 0)
    {
    	xa = a.x;
    	a2 = (c.y - d.y) / (c.x - d.x);
    	b2 = c.y - a2 * c.x;
    	a1 = a2 * xa + b2;
    	if (c.x <= xa && d.x >= xa && min_cross(a.y, b.y) <= a1 &&
            max_cross(a.y, b.y) >= a1)
            return (1);
        return (0);
    }
    if (c.x - d.x == 0)
    {
    	xa = c.x;
    	a1 = (a.y - b.y) / (a.x - b.x);
		b1 = a.y - a1 * a.x;
		a2 = a1 * xa + b1;
		if (a.x <= xa && b.x >= xa && min_cross(c.y, b.y) <= a2 &&
		       max_cross(c.y, d.y) >= a2) 
		    return (1);
		return (0);
    }
	a1 = (a.y - b.y) / (a.x - b.x);
	a2 = (c.y - d.y) / (c.x - d.x);
	b1 = a.y - a1 * a.x;
	b2 = c.y - a2 * c.x;
	if (a1 == a2)
		return (0);
	xa = (b2 - b1) / (a1 - a2);
	if ((xa < max_cross(a.x, c.x)) || (xa > max_cross(b.x, d.x)))
		return (0);
	return (1);
}

int		check_wall_crossing(t_doom *doom, int nb, int i)
{
	t_cross a;
	t_cross b;
	t_cross c;
	t_cross d;

	a.x = doom->play[nb].t.x;
	a.y = doom->play[nb].t.z;
	b.x = doom->play[doom->n_play].t.x;
	b.y = doom->play[doom->n_play].t.z;
	c.x = doom->toch[doom->sec[i].pts[0]].x;
	c.y = doom->toch[doom->sec[i].pts[0]].z;
	d.x = doom->toch[doom->sec[i].pts[3]].x;
	d.y = doom->toch[doom->sec[i].pts[3]].z;
	return (check_cross(a, b, c, d));
}
