/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_multipl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 11:06:39 by tbahlai           #+#    #+#             */
/*   Updated: 2019/10/06 11:06:40 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	mult_text(t_l *l, int x, int y, SDL_Color color)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*s;

	f.x = x;
	f.y = y;
	if (l->f_numpl == 0)
		s = "2";
	if (l->f_numpl == 1 || l->f_numpl == -2)
		s = "3";
	if (l->f_numpl == 2 || l->f_numpl == -1)
		s = "4";
	if (x == l->w / 5)
		s = "Players\0";
	message = TTF_RenderText_Solid(l->ttf, s, color);
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
}

void	get_h(t_l *l, SDL_Rect *btn)
{
	if (l->w == 640)
		btn->h = 25;
	if (l->w == 1024)
		btn->h = 30;
	if (l->w == 1280)
		btn->h = 35;
	if (l->w == 1500)
		btn->h = 40;
}

void	set_flag(t_l *l)
{
	if (l->f_numpl == 0)
		l->m.num_play = 2;
	if (l->f_numpl == 1 || l->f_numpl == -2)
		l->m.num_play = 3;
	if (l->f_numpl == 2 || l->f_numpl == -1)
		l->m.num_play = 4;
}

void	num_play(t_l *l, SDL_Rect *right)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	btn.x = right->w + 5;
	btn.y = l->h / 1.5 + 3;
	btn.w = l->w / 8 - right->w;
	get_h(l, &btn);
	SDL_GetMouseState(&x, &y);
	l->color_btn = (x >= btn.x && x <= btn.x + btn.w && y >= btn.y
	&& y <= btn.y + btn.h) ? 1 : 3;
	SDL_BlitScaled(l->texture[l->color_btn], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP &&
		l->event.button.button == SDL_BUTTON_LEFT && l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w && l->event.button.y >= btn.y &&
		l->event.button.y <= btn.y + btn.h)
		set_flag(l);
	mult_text(l, (right->w + 5) +
		(l->w / 8 - right->w) / 2.5, btn.y, (SDL_Color){80, 10, 10, 0});
	mult_text(l, l->w / 5, btn.y, (SDL_Color){255, 140, 10, 0});
}
