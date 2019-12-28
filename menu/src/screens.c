/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:54:31 by tbahlai           #+#    #+#             */
/*   Updated: 2019/12/28 18:18:12 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

void	screen1(t_l *l)
{
	SDL_Rect	back;
	int			fl;
	int			o;

	fl = -1;
	back.x = 0;
	back.y = 0;
	back.h = l->h;
	back.w = l->w;
	SDL_BlitScaled(l->texture[7], NULL, l->sur, &back);
	o = (l->f_mult == 1) ? 8 : 6;
	while (++fl < o)
		start_btn(l, fl);
		
}

void	choose_screen(t_l *l)
{
	SDL_Rect back;

	back.x = 0;
	back.y = 0;
	back.h = l->h;
	back.w = l->w;
	if (l->screen == 1)
		screen1(l);
	if (l->screen == 3)
	{
		SDL_BlitScaled(l->texture[4], NULL, l->sur, &back);
		setting_btn(l, 0);
		setting_btn(l, 1);
	}
	if (l->screen == 4)
		exit(0);
	if (l->screen == 5)
	{
		start_editor(l->win);
		l->screen = 3;
	
	}
}
