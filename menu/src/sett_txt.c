/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sett_txt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:38:03 by tbahlai           #+#    #+#             */
/*   Updated: 2019/12/28 16:31:27 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

void	text_on_off(t_l *l, int x, int y, int step)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*s;

	f.x = x;
	f.y = y;
	if (step == 0)
	{
		if (l->m.flag_mus == 0)
			s = "OFF\0";
		else if (l->m.flag_mus == 1)
			s = "ON\0";
	}
	else
	{
		if (l->m.flag_soun == 0)
			s = "OFF\0";
		else if (l->m.flag_soun == 1)
			s = "ON\0";
	}
	message = TTF_RenderText_Solid(l->ttf, s, l->text_color);
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
}

void	btn_text_s(t_l *l, int x, int y)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*s;

	f.x = x;
	f.y = y;
	if (l->f_btn == 0)
		s = "640 x 480\0";
	else if (l->f_btn == 1 || l->f_btn == -3)
		s = "1024 x 768\0";
	else if (l->f_btn == 2 || l->f_btn == -2)
		s = "1280 x 1024\0";
	else if (l->f_btn == 3 || l->f_btn == -1)
		s = "1500 x 1200\0";
	message = TTF_RenderText_Solid(l->ttf, s, l->text_color);
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
}

void	just_text(t_l *l, int flag, int step)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*s;

	f.x = l->w - (l->w / 3);
	f.y = l->h / 8 + step;
	if (flag == 0)
		s = "Music\0";
	else
		s = "Sounds effects\0";
	message = TTF_RenderText_Solid(l->ttf, s, (SDL_Color){255, 140, 10, 0});
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
	on_off(l, step);
}

void	txt_back_info(t_l *l, int x, int y, int fl)
{
	SDL_Surface	*message;
	SDL_Rect	f;
	char		*s;

	f.x = x;
	f.y = y;
	if (fl == 0)
		s = "Info\0";
	else if (fl == 1)
		s = "Back\0";
	message = TTF_RenderText_Solid(l->ttf, s, l->text_color);
	SDL_BlitSurface(message, NULL, l->sur, &f);
	SDL_FreeSurface(message);
}
