/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:29:50 by tbahlai           #+#    #+#             */
/*   Updated: 2020/01/30 13:42:34 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

void	get_heig(t_l *l, SDL_Rect *btn)
{
	if (l->w == 640)
		btn->h = 35;
	if (l->w == 1024)
		btn->h = 45;
	if (l->w == 1280)
		btn->h = 50;
	if (l->w == 1500)
		btn->h = 60;
}

void	start_txt(t_l *l, int x, int y, int fl)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*s;

	f.x = x;
	f.y = y;
	if (fl == 0)
		s = "Create map\0";
	if (fl == 1)
		s = "Back\0";
	if (fl == 2)
		s = "Easy\0";
	if (fl == 3)
		s = "Medium\0";
	if (fl == 4)
		s = "Hard\0";
	if (fl == 5)
		s = "Multiplayer\0";
	if (fl == 6)
		s = "Server\0";
	if (fl == 7)
		s = "Player\0";
	message = TTF_RenderText_Solid(l->ttf, s, l->text_color);
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
}

void	select_screen(int fl, t_l *l)
{
	if (fl == 0)
		l->screen = 5;
	else if (fl == 1)
		l->screen = 0;
	else if (fl == 2 || fl == 3 || fl == 4)
	{
		l->m.f_run = 1;
		l->m.f_diffic = (fl == 2) ? 1 : l->m.f_diffic;
		l->m.f_diffic = (fl == 3) ? 2 : l->m.f_diffic;
	}
	else if (fl == 5)
		l->f_mult = 1;
	else if (fl == 6)
	{
		l->m.f_ser = 1;
		l->m.f_play = 0;
	}
	else if (fl == 7)
	{
		l->m.f_play = 1;
		l->m.f_ser = 0;
		l->m.num_play = 0;
	}
}

void	start_btn(t_l *l, int fl)
{
	SDL_Rect	btn;
	int			x;
	int			y;

	btn_param(l, &btn, fl);
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
			select_screen(fl, l);	
	start_txt(l, btn.x + (btn.w / 4), btn.y + 6, fl);
	if (l->m.f_ser)
	{
		arrow_l(l);
		arrow_r(l);
	}
}
