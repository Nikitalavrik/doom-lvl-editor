/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:19:58 by tbahlai           #+#    #+#             */
/*   Updated: 2020/02/16 16:29:58 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/doom.h"

void	draw_sky(t_doom *doom, SDL_Rect renderquad, SDL_Rect windowquad)
{
	if (renderquad.x + doom->skybox.size.h -
	(doom->skybox.indent * 2) > doom->skybox.size.w)
	{
		windowquad.x = windowquad.w;
		windowquad.y = 0;
		windowquad.h = doom->h;
		windowquad.w = doom->w - windowquad.x;
		renderquad.h = doom->skybox.size.h - (doom->skybox.indent * 2);
		renderquad.x = 0;
		renderquad.w = doom->skybox.size.h -
		(doom->skybox.indent * 2) - renderquad.w;
		renderquad.y = doom->skybox.indent + doom->play[doom->n_play].angle_x * 2;
		SDL_BlitSurface(doom->skybox.tex,
		&renderquad, doom->surface, &windowquad);
	}
}

void	skybox(t_doom *doom)
{
	SDL_Rect renderquad;
	SDL_Rect windowquad;

	windowquad.x = 0;
	windowquad.y = 0;
	windowquad.h = doom->h;
	windowquad.w = doom->w;
	renderquad.h = doom->skybox.size.h - (doom->skybox.indent * 2);
	renderquad.x = (360 - doom->play[doom->n_play].angle_y) *
	doom->skybox.kof_y + doom->skybox.count;
	if (renderquad.x >= doom->skybox.size.w)
		renderquad.x -= doom->skybox.size.w;
	if (renderquad.x + doom->skybox.size.h -
	(doom->skybox.indent * 2) > doom->skybox.size.w)
	{
		renderquad.w = doom->skybox.size.w - renderquad.x;
		windowquad.w = doom->w * renderquad.w /
		(doom->skybox.size.h - (doom->skybox.indent * 2));
	}
	else
		renderquad.w = doom->skybox.size.h - (doom->skybox.indent * 2);
	renderquad.y = doom->skybox.indent + doom->play[doom->n_play].angle_x * 2;
	SDL_BlitSurface(doom->skybox.tex, &renderquad, doom->surface, &windowquad);
	draw_sky(doom, renderquad, windowquad);
}

void	init_skybox(t_doom *doom)
{
	SDL_Surface *text;

	text = IMG_Load("../text/skybox/sky.bmp");
	doom->skybox.size.x = 0;
	doom->skybox.size.y = 0;
	doom->skybox.size.w = doom->w * 3.8;
	doom->skybox.size.h = doom->h * 2.5;
	doom->skybox.count = 0;
	doom->skybox.tex = SDL_CreateRGBSurface(0,
			doom->skybox.size.w, doom->skybox.size.h, 32, 0, 0, 0, 0);
	SDL_BlitScaled(text, NULL, doom->skybox.tex, NULL);
	doom->skybox.kof_y = ((float)doom->skybox.size.w / 360.0);
	doom->skybox.indent = (doom->skybox.size.h * 40) / 200;
	SDL_FreeSurface(text);
}
