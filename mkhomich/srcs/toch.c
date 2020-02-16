/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhomich <mkhomich@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:36:59 by mkhomich          #+#    #+#             */
/*   Updated: 2019/09/01 17:37:00 by mkhomich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	*threading(void *data)
{
	t_pth	*pth;
	int		x;
	int		y;

	pth = (t_pth*)data;
	y = pth->sq.y;
	while (y < pth->sq.y + pth->sq.h)
	{
		x = pth->sq.x;
		while (x < pth->sq.x + pth->sq.w)
		{
			if (y < pth->sec->tex_y && x < pth->sec->tex_x &&
					(pth->sec->toch[y][x].tz2 > pth->doom->min_z ||
				pth->sec->toch[y][x + 1].tz2 > pth->doom->min_z ||
				pth->sec->toch[y + 1][x].tz2 > pth->doom->min_z ||
				pth->sec->toch[y + 1][x + 1].tz2 > pth->doom->min_z))
			{
				render_tr1(pth->doom, pth->sec, x, y);
				render_tr2(pth->doom, pth->sec, x, y);
			}
			x++;
		}
		y++;
	}
	return (pth);
}

void	viem_sec_toch(t_doom *doom, t_sec *sec)
{
	int			ch_x;
	int			ch_y;
	int			pthr;
	pthread_t	thread[THREADS];
	t_pth		pth[THREADS];

	if (sec->tex_x >= (THREADS >> 1) && sec->tex_y >= 2)
	{
		ch_x = (sec->tex_x + 1) / (THREADS >> 1);
		ch_y = (sec->tex_y + 1) / 2;
		pthr = -1;
		while (++pthr < THREADS)
		{
			pth[pthr].base = (pthr >= (THREADS >> 1)) ? 1 : 0;
			pth[pthr].doom = doom;
			pth[pthr].sec = sec;
			pth[pthr].sq.x = ch_x * ((pth[pthr].base) ?
			(pthr - (THREADS >> 1)) : pthr);
			pth[pthr].sq.y = (pth[pthr].base) ? (ch_y) : 0;
			pth[pthr].sq.w = ((pthr == (THREADS >> 1) - 1 ||
			pthr == THREADS - 1)) ? (sec->tex_x - pth[pthr].sq.x + 1) : ch_x;
			pth[pthr].sq.h = (pth[pthr].base) ? (sec->tex_y - ch_y + 1) : ch_y;
			pthread_create(&thread[pthr], NULL, threading, &pth[pthr]);
		}
		pthr = -1;
		while (++pthr < THREADS)
			pthread_join(thread[pthr], NULL);
	}
	else
	{
		pth[0].doom = doom;
		pth[0].sec = sec;
		pth[0].sq.x = 0;
		pth[0].sq.y = 0;
		pth[0].sq.w = sec->tex_x + 1;
		pth[0].sq.h = sec->tex_y + 1;
		threading(&pth[0]);
	}
}
