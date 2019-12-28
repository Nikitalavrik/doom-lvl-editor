/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sett_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:44:29 by tbahlai           #+#    #+#             */
/*   Updated: 2019/12/28 16:31:24 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

void	get_y_h(t_l *l, SDL_Rect *btn)
{
	if (l->w == 640)
	{
		btn->y = l->h / 8 + 90;
		btn->h = 40;
	}
	if (l->w == 1024)
	{
		btn->h = 50;
		btn->y = l->h / 8 + 120;
	}
	if (l->w == 1280)
	{
		btn->h = 60;
		btn->y = l->h / 8 + 150;
	}
	if (l->w == 1500)
	{
		btn->h = 70;
		btn->y = l->h / 8 + 180;
	}
}

void	back_and_info(t_l *l, int flag, SDL_Rect *btn)
{
	if (flag == 0)
	{
		btn->x = l->w - (l->w / 3) - 15;
		btn->w = (l->w - btn->x) / 2 - 5;
	}
	else
	{
		btn->x = (l->w - (l->w / 3) - 15) + ((l->w - btn->x) / 2 + 5);
		btn->w = (l->w - btn->x) - 5;
	}
	get_y_h(l, btn);
}

void	wid_and_heig(SDL_Rect *btn, t_l *l)
{
	if (l->w == 640)
		*btn = (SDL_Rect){450, 7, 150, 40};
	else if (l->w == 1024)
		*btn = (SDL_Rect){800, 7, 190, 40};
	else if (l->w == 1280)
		*btn = (SDL_Rect){975, 7, 270, 50};
	else if (l->w == 1500)
		*btn = (SDL_Rect){1150, 7, 310, 60};
}

void	arrow_wid_and_heig(SDL_Rect *btn, t_l *l)
{
	btn->y = 10;
	if (l->w == 640)
	{
		btn->w = 40;
		btn->h = 30;
	}
	if (l->w == 1024)
	{
		btn->w = 45;
		btn->h = 35;
	}
	if (l->w == 1280)
	{
		btn->w = 50;
		btn->h = 40;
	}
	if (l->w == 1500)
	{
		btn->w = 55;
		btn->h = 45;
	}
}
