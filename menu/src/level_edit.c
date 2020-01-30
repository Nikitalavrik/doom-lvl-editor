/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:06:40 by tbahlai           #+#    #+#             */
/*   Updated: 2020/01/30 13:29:57 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

void	print_menu(t_l *l)
{
	draw_back(l);
	l->flag = -1;
	while (++l->flag < 4)
		draw_btn(l);
}

void	init_value(t_l *l, int w, int h)
{
	if (w == 0 && h == 0)
	{
		l->w = 640;
		l->h = 480;
	}
	else
	{
		SDL_DestroyWindow(l->win);
		l->w = w;
		l->h = h;
		rewrite_font(l);
	}
	l->win = SDL_CreateWindow("Create Level", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, l->w, l->h, SDL_WINDOW_SHOWN);
	l->sur = SDL_GetWindowSurface(l->win);
	l->w1 = l->w / 2.6;
	l->h1 = l->h - (l->h / 3);
}

void	set_values(t_l *l)
{
	l->line.x1 = -1;
	l->screen = 0;
	l->color_btn = 1;
	l->f_btn = 0;
	l->anim = 0;
}

int		level_edit(t_l *l)
{
	int a;
	int b;

	a = 0;
	b = 0;
	l->a = 1;
	init_value(l, 0, 0);
	load_text_font(l);
	set_values(l);
	while (l->a)
	{
		while (SDL_PollEvent(&l->event))
			event(l);
		if (!(l->screen))
			print_menu(l);
		choose_screen(l);
		SDL_UpdateWindowSurface(l->win);
	}
	return (0);
}

void	draw_back(t_l *l)
{
	SDL_Rect	back;

	back = (SDL_Rect){0, 0, l->w, l->h};
	SDL_BlitScaled(l->texture[2], NULL, l->sur, &back);
}
