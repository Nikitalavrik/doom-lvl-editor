/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhomich <mkhomich@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:31:50 by mkhomich          #+#    #+#             */
/*   Updated: 2020/03/02 17:31:52 by mkhomich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

float	move_up(t_doom *doom, int pl)
{
	float line_x;
	float line_z;
	float step_x;
	float step_z;

	step_x = SDL_cos(doom->play[pl].angle_y * PI / 180);
	step_z = SDL_sin(doom->play[pl].angle_y * PI / 180);
	line_x = coliz_pl(doom, doom->play[pl].t.x,
			doom->play[pl].t.z + step_x * doom->play[pl].speed, pl);
	line_z = coliz_pl(doom, doom->play[pl].t.x - step_z
	* doom->play[pl].speed, doom->play[pl].t.z, pl);
	if (line_x > BOUND)
		doom->play[pl].t.z += step_x * doom->play[pl].speed;
	if (line_z > BOUND)
		doom->play[pl].t.x -= step_z * doom->play[pl].speed;
	if (doom->play[pl].f_move == 0)
		doom->play[pl].f_move = 1;
	return ((line_x < line_z) ? line_x : line_z);
}

float	move_down(t_doom *doom, int pl)
{
	float line_x;
	float line_z;
	float step_x;
	float step_z;

	step_x = SDL_cos(doom->play[pl].angle_y * PI / 180);
	step_z = SDL_sin(doom->play[pl].angle_y * PI / 180);
	line_x = coliz_pl(doom, doom->play[pl].t.x,
			doom->play[pl].t.z - step_x * doom->play[pl].speed, pl);
	line_z = coliz_pl(doom, doom->play[pl].t.x + step_z
	* doom->play[pl].speed, doom->play[pl].t.z, pl);
	if (line_x > BOUND)
		doom->play[pl].t.z -= step_x * doom->play[pl].speed;
	if (line_z > BOUND)
		doom->play[pl].t.x += step_z * doom->play[pl].speed;
	if (doom->play[pl].f_move == 0)
		doom->play[pl].f_move = 1;
	return ((line_x < line_z) ? line_x : line_z);
}

float	move_left(t_doom *doom, int pl)
{
	float line_x;
	float line_z;
	float step_x;
	float step_z;

	step_x = SDL_sin(doom->play[pl].angle_y * PI / 180);
	step_z = SDL_cos(doom->play[pl].angle_y * PI / 180);
	line_x = coliz_pl(doom, doom->play[pl].t.x,
			doom->play[pl].t.z - step_x * doom->play[pl].speed, pl);
	line_z = coliz_pl(doom, doom->play[pl].t.x - step_z
	* doom->play[pl].speed, doom->play[pl].t.z, pl);
	if (line_x > BOUND)
		doom->play[pl].t.z -= step_x * doom->play[pl].speed;
	if (line_z > BOUND)
		doom->play[pl].t.x -= step_z * doom->play[pl].speed;
	if (doom->play[pl].f_move == 0)
		doom->play[pl].f_move = 1;
	return ((line_x < line_z) ? line_x : line_z);
}

float	move_right(t_doom *doom, int pl)
{
	float line_x;
	float line_z;
	float step_x;
	float step_z;

	step_x = SDL_sin(doom->play[pl].angle_y * PI / 180);
	step_z = SDL_cos(doom->play[pl].angle_y * PI / 180);
	line_x = coliz_pl(doom, doom->play[pl].t.x,
			doom->play[pl].t.z + step_x * doom->play[pl].speed, pl);
	line_z = coliz_pl(doom, doom->play[pl].t.x + step_z
	* doom->play[pl].speed, doom->play[pl].t.z, pl);
	if (line_x > BOUND)
		doom->play[pl].t.z += step_x * doom->play[pl].speed;
	if (line_z > BOUND)
		doom->play[pl].t.x += step_z * doom->play[pl].speed;
	if (doom->play[pl].f_move == 0)
		doom->play[pl].f_move = 1;
	return ((line_x < line_z) ? line_x : line_z);
}