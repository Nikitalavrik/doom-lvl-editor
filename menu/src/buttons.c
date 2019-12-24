/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahlai <tbahlai@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:06:40 by tbahlai           #+#    #+#             */
/*   Updated: 2019/08/28 18:06:40 by tbahlai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	get_wid_heig(SDL_Rect *btn, int *a, int flag, t_l *l)
{
	btn->x = l->w1;
	if (l->w == 640 && l->h == 480)
	{
		*a = (flag * 40) - 15;
		btn->h = 38;
		btn->w = 140;
	}
	else if (l->w == 1024 && l->h == 768)
	{
		*a = (flag * 60) - 15;
		btn->h = 55;
		btn->w = 200;
	}
	else if (l->w == 1280 && l->h == 1024)
	{
		*a = (flag * 80) - 15;
		btn->h = 70;
		btn->w = 270;
	}
	else if (l->w == 1500 && l->h == 1200)
	{
		*a = (flag * 100) - 15;
		btn->h = 90;
		btn->w = 320;
	}
}

void	get_font_size(t_l *l)
{
	if (l->w == 640)
		l->font_size = 26;
	else if (l->w == 1024)
		l->font_size = 32;
	else if (l->w == 1280)
		l->font_size = 42;
	else if (l->w == 1500)
		l->font_size = 52;
}

void	get_for_text(t_l *l, int *a, int *b)
{
	if (l->w == 640)
	{
		*b = (l->flag * 40) - 5;
		*a = (l->flag == 1 || l->flag == 2) ? -35 : (l->flag * 1.6) - 25;
	}
	else if (l->w == 1024)
	{
		*b = (l->flag * 60);
		*a = (l->flag == 1 || l->flag == 2) ? -55 : (l->flag * 1.6) - 45;
	}
	else if (l->w == 1280)
	{
		*b = (l->flag * 80);
		*a = (l->flag == 1 || l->flag == 2) ? -55 : (l->flag * 1.6) - 45;
	}
	else if (l->w == 1500)
	{
		*b = (l->flag * 100) + 5;
		*a = (l->flag == 1 || l->flag == 2) ? -75 : (l->flag * 1.6) - 55;
	}
}

void	btn_text(t_l *l, int x, int y)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	int			a;
	int			b;
	char		*s;

	a = 0;
	b = 0;
	get_for_text(l, &a, &b);
	f.x = x + a;
	f.y = y + b;
	if (l->flag == 0)
		s = "Start\0";
	else if (l->flag == 1)
		s = "Continue\0";
	else if (l->flag == 2)
		s = "Settings\0";
	else if (l->flag == 3)
		s = "Exit\0";
	message = TTF_RenderText_Solid(l->ttf, s, l->text_color);
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
}

void	draw_btn(t_l *l)
{
	SDL_Rect	btn;
	int			x;
	int			y;
	int			a;

	a = 0;
	get_wid_heig(&btn, &a, l->flag, l);
	btn.y = l->h1 + a;
	SDL_GetMouseState(&x, &y);
	l->color_btn = (x >= btn.x && x <= btn.x + btn.w && y >= btn.y
	&& y <= btn.y + btn.h) ? 1 : 3;
	if (l->flag == 1 && l->m.flag_cont == 0)
		l->color_btn = 3;
	SDL_BlitScaled(l->texture[l->color_btn], NULL, l->sur, &btn);
	if (l->event.type == SDL_MOUSEBUTTONUP
		&& l->event.button.button == SDL_BUTTON_LEFT
		&& l->event.button.x >= btn.x && l->event.button.x <= btn.x + btn.w
		&& l->event.button.y >= btn.y && l->event.button.y <= btn.y + btn.h)
	{
		l->screen = l->flag + 1;
		l->black = 1;
		if (l->m.flag_cont == 0 && l->flag == 1)
			l->screen = 0;
	}
	btn_text(l, l->w / 2, l->h1);
}
