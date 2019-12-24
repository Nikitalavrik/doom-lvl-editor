/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_mult_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:05:11 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/20 15:05:11 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	arrow_l(t_l *l)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	arrow_wid_and_heig(&btn, l);
	btn.x = l->w / 8;
	btn.y = l->h / 1.5;
	SDL_GetMouseState(&x, &y);
	SDL_BlitScaled(l->texture[5], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y
		&& l->event.button.y <= btn.y + btn.h && l->f_numpl < 3)
	{
		l->event.type = SDL_FIRSTEVENT;
		l->f_numpl++;
		if (l->f_numpl == 3)
			l->f_numpl = 0;
	}
}

void	arrow_r(t_l *l)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	arrow_wid_and_heig(&btn, l);
	btn.x = 5;
	btn.y = l->h / 1.5;
	SDL_GetMouseState(&x, &y);
	SDL_BlitScaled(l->texture[6], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y
		&& l->event.button.y <= btn.y + btn.h && l->f_numpl > -3)
	{
		l->event.type = SDL_FIRSTEVENT;
		l->f_numpl--;
		if (l->f_numpl == -3)
			l->f_numpl = 0;
	}
	num_play(l, &btn);
}
