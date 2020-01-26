/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:08:32 by mkhomich          #+#    #+#             */
/*   Updated: 2019/12/01 16:58:34 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	rotate_y(t_doom *doom, t_toch *toch)
{
	toch->tx1 = toch->x - doom->play[doom->n_play].t.x;
	toch->ty1 = toch->y - doom->play[doom->n_play].t.y - ((doom->play[doom->n_play].crouch) ? 4 : 8);
	toch->tz1 = toch->z - doom->play[doom->n_play].t.z;
	toch->tx2 = toch->tx1 *
			SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) + toch->tz1
			* SDL_sin(doom->play[doom->n_play].angle_y * PI / 180);
	toch->tz2 = -toch->tx1 *
			SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) + toch->tz1
			* SDL_cos(doom->play[doom->n_play].angle_y * PI / 180);
	toch->ty2 = toch->ty1;
}

void	core_deg(t_doom *doom, t_toch *toch)
{
	toch->tx1 = IGRX + toch->tx2 / toch->tz2 * IGRX;
	toch->ty1 = IGRY - toch->ty2 / toch->tz2 * IGRY - doom->play[doom->n_play].angle_x * 3;
}

void	rotate_sec(t_doom *doom, t_sec *sec)
{
	int x;
	int y;

	y = 0;
	while (y < sec->tex_y + 1)
	{
		x = 0;
		while (x < sec->tex_x + 1.0)
		{
			if (sec->f_move && sec->p_move > 0 && sec->p_move < 1)
			{
				sec->toch[y][x].tx1 = (sec->toch[y][x].x + sec->p_move * sec->v2.x) - doom->play[doom->n_play].t.x;
				sec->toch[y][x].ty1 = (sec->toch[y][x].y + sec->p_move * sec->v2.y) - doom->play[doom->n_play].t.y - ((doom->play[doom->n_play].crouch) ? 4 : 8);
				sec->toch[y][x].tz1 = (sec->toch[y][x].z + sec->p_move * sec->v2.z) - doom->play[doom->n_play].t.z;
			}
			else
			{
				sec->toch[y][x].tx1 = sec->toch[y][x].x - doom->play[doom->n_play].t.x;
				sec->toch[y][x].ty1 = sec->toch[y][x].y - doom->play[doom->n_play].t.y - ((doom->play[doom->n_play].crouch) ? 4 : 8);
				sec->toch[y][x].tz1 = sec->toch[y][x].z - doom->play[doom->n_play].t.z;
			}
			sec->toch[y][x].tx2 = sec->toch[y][x].tx1 *
					SDL_cos(doom->play[doom->n_play].angle_y * PI / 180) + sec->toch[y][x].tz1
					* SDL_sin(doom->play[doom->n_play].angle_y * PI / 180);
			sec->toch[y][x].tz2 = -sec->toch[y][x].tx1 *
					SDL_sin(doom->play[doom->n_play].angle_y * PI / 180) + sec->toch[y][x].tz1
					* SDL_cos(doom->play[doom->n_play].angle_y * PI / 180);
			sec->toch[y][x].ty2 = sec->toch[y][x].ty1;
			core_deg(doom, &sec->toch[y][x]);
			x++;
		}
		y++;
	}
}
