/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_btn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:17:13 by tbahlai           #+#    #+#             */
/*   Updated: 2019/12/28 16:31:15 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

int		animation_btn(t_l *l, SDL_Rect *btn, int fl)
{
	if (fl == 2 || fl == 3 || fl == 4)
	{
		// if (l->anim % 25)
		// {
		//btn->y = 0;
		while (l->anim < 20)
		{
			btn->w += 10;
			l->anim++;
			printf("anim === %d\n", l->anim);
		}
		
		if (l->anim > 100)
		{
			l->anim = 0;
			printf("i am hwew\n");
		}
		l->anim++;
		return (1);
	}
	return (0);
}

void	add_param(t_l *l, SDL_Rect *btn, int fl)
{
	if (fl == 2 || fl == 3 || fl == 4 || fl == 6 || fl == 7)
		btn->w = l->w / 6;
	if (fl == 2)
		btn->y = l->h / 12;
	if (fl == 3)
		btn->y = l->h / 6;
	if (fl == 4)
		btn->y = l->h / 4;
	if (fl == 1)
		btn->x = (l->w / 4) + 10;
	else
		btn->x = 5;
	// if (fl == 2 || fl == 3 || fl == 4)
	// 	animation_btn(l, btn, fl);
}

void	btn_param(t_l *l, SDL_Rect *btn, int fl)
{
	get_heig(l, btn);
	if (fl == 0)
	{
		btn->w = l->w / 4;
		btn->y = l->h - btn->h - 10;
	}
	if (fl == 1)
	{
		btn->w = l->w / 9;
		btn->y = l->h - btn->h - 10;
	}
	add_param(l, btn, fl);
	if (fl == 6 || fl == 7)
	{
		btn->y = l->h / 1.7;
		if (fl == 7)
			btn->x = btn->w + 10;
	}
	if (fl == 5)
	{
		btn->y = l->h / 2;
		btn->w = l->w / 4;
	}
}
