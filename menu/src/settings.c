/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:31:11 by tbahlai           #+#    #+#             */
/*   Updated: 2019/09/03 12:31:11 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	arrow_right(t_l *l, int a)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	arrow_wid_and_heig(&btn, l);
	btn.x = (l->w == 640) ? l->w - a - btn.w * 2 : l->w - a - btn.w * 1.5;
	SDL_GetMouseState(&x, &y);
	SDL_BlitScaled(l->texture[6], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y
		&& l->event.button.y <= btn.y + btn.h && l->f_btn < 4)
	{
		l->event.type = SDL_FIRSTEVENT;
		l->f_btn++;
		if (l->f_btn == 4)
			l->f_btn = 0;
	}
}

void	button_wind_size(t_l *l)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	wid_and_heig(&btn, l);
	SDL_GetMouseState(&x, &y);
	l->color_btn = (x >= btn.x && x <= btn.x + btn.w && y >= btn.y
	&& y <= btn.y + btn.h) ? 1 : 3;
	SDL_BlitScaled(l->texture[l->color_btn], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP &&
		l->event.button.button == SDL_BUTTON_LEFT && l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w && l->event.button.y >= btn.y &&
		l->event.button.y <= btn.y + btn.h)
	{
		if (l->f_btn == 0)
			init_value(l, 640, 480);
		else if (l->f_btn == 1 || l->f_btn == -3)
			init_value(l, 1024, 768);
		else if (l->f_btn == 2 || l->f_btn == -2)
			init_value(l, 1280, 1024);
		else if (l->f_btn == 3 || l->f_btn == -1)
			init_value(l, 1500, 1200);
	}
	btn_text_s(l, btn.x + (btn.w / 4), btn.y + 6);
	arrow_right(l, btn.w);
}

void	arrow_left(t_l *l)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	arrow_wid_and_heig(&btn, l);
	btn.x = l->w - btn.w;
	btn.y = 10;
	SDL_GetMouseState(&x, &y);
	SDL_BlitScaled(l->texture[5], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y
		&& l->event.button.y <= btn.y + btn.h && l->f_btn > -4)
	{
		l->event.type = SDL_FIRSTEVENT;
		l->f_btn--;
		if (l->f_btn == -4)
			l->f_btn = 0;
	}
	button_wind_size(l);
}

void	on_off(t_l *l, int step)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	wid_and_heig(&btn, l);
	btn.w /= 3;
	btn.x = l->w - btn.w - 5;
	btn.y = l->h / 8 + step - 10;
	SDL_GetMouseState(&x, &y);
	SDL_BlitScaled(l->texture[3], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y
		&& l->event.button.y <= btn.y + btn.h)
	{
		l->event.type = SDL_FIRSTEVENT;
		if (step == 0)
			l->m.flag_mus = (l->m.flag_mus == 0) ? 1 : 0;
		else
			l->m.flag_soun = (l->m.flag_soun == 0) ? 1 : 0;
	}
	text_on_off(l, btn.x + (btn.w / 4), btn.y + 5, step);
}

void	setting_btn(t_l *l, int fl)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	back_and_info(l, fl, &btn);
	SDL_GetMouseState(&x, &y);
	l->color_btn = (x >= btn.x && x <= btn.x + btn.w && y >= btn.y
	&& y <= btn.y + btn.h) ? 1 : 3;
	SDL_BlitScaled(l->texture[l->color_btn], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x
		&& l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y
		&& l->event.button.y <= btn.y + btn.h)
	{
		if (fl == 0)
			l->screen = 4;
		else
			l->screen = 0;
	}
	arrow_left(l);
	txt_back_info(l, btn.x + (btn.w / 3), btn.y + 10, fl);
	just_text(l, 1, (l->w == 640) ? 50 : 60);
	just_text(l, 0, 0);
}
